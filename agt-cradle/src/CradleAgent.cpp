
#include <pargo/approx/FourierFA.h>

#include <pargo/obs/GnuplotObserver.h>
#include <pargo/CRADLE.h>

#include <rlglue/Agent_common.h> /* agent_ function prototypes and RL-Glue types */
#include <rlglue/utils/C/RLStruct_util.h> /* helpful functions for allocating structs and cleaning them up */
#include <rlglue/utils/C/TaskSpec_Parser.h>

#include <cstring> /* for strcmp */
#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <stdexcept>


#define EVALUATE_POLICY false


using namespace std;
using namespace pargo;

static action_t this_action;
static action_t last_action;

static observation_t *last_observation=0;
static double totalReward = 0;


static Poll *alg ( NULL );
static GnuplotObserver obs ( "points.txt" );

static vector<double> fromFile;
static ofstream stateFile;
static vector<double> params;
static vector<BoundsPair> actBounds;
static BoundsPair parBounds(make_pair(-10.,10.));
static vector<LinearFA*> policy;

static CRADLE::ParamType par;

static taskspec_t task;

static bool ended = true;



static void loadParameters();
static void  applyPolicy (const observation_t *obs );



void agent_init ( const char* task_spec ) {
    /*Seed the random number generator*/

    srand ( time ( 0 ) );
    /*Here is where you might allocate storage for parameters (value function or policy, last action, last observation, etc)*/

	loadParameters();
	
	ofstream startTime("start_time"); //create a file to see the starting time
	startTime.close();
	
    /*Here you would parse the task spec if you felt like it*/
    cout << task_spec << endl;
    int task_failed = decode_taskspec(&task,task_spec);
    if(task_failed)
        throw runtime_error( "parsing task failed with code " + task_failed);

    if(getNumIntAct(&task) > 0)
        throw runtime_error( "this agent does not support integer actions");

    if(getNumIntObs(&task) > 0)
        throw runtime_error( "this agent does not support integer observations");

    /*Allocate memory for actions using utility functions from RLStruct_util*/
    allocateRLStruct ( &this_action,0,getNumDoubleAct(&task),0 );
    last_observation=allocateRLStructPointer ( 0,getNumDoubleObs(&task),0 );


    //read bounds
    vector<BoundsPair> obsBounds;
    for (int i=0; i<last_observation->numDoubles; ++i) {
        if(isDoubleObsMax_posInf(&task,i) || isDoubleObsMax_special(&task,i) ||
                isDoubleObsMax_unspec(&task,i) ||isDoubleObsMin_negInf(&task,i) ||
                isDoubleObsMin_special(&task,i) || isDoubleObsMin_unspec(&task,i)) {

            throw runtime_error("observation " + i + string("'s bounds are not compatible with this agent"));
        }

        obsBounds.push_back(make_pair(getDoubleObsMin(&task,i),getDoubleObsMax(&task,i)));
    }

    for(int i=0; i<getNumDoubleAct(&task); ++i) {
        if(isDoubleActMax_posInf(&task,i) || isDoubleActMax_special(&task,i) ||
                isDoubleActMax_unspec(&task,i) ||isDoubleActMin_negInf(&task,i) ||
                isDoubleActMin_special(&task,i) || isDoubleActMin_unspec(&task,i)) {

            throw runtime_error("action "+i+ string("'s bounds are not compatible with this agent"));
        }

        actBounds.push_back(make_pair(getDoubleActMin(&task,i),getDoubleActMax(&task,i)));
    }


    ifstream pointFile("vector.txt");
    istream_iterator<double> intstream(pointFile), eof;
    copy(intstream,eof,back_inserter(fromFile));
    pointFile.close();

    //Set up the policy
    //SETTINGS

    FourierCoefficientGenerator *gen = new IndependentFourierCoefficientGenerator(getNumDoubleObs(&task),1);

    for(int i=0; i<getNumDoubleAct(&task); ++i) {
        policy.push_back( new FourierFA(obsBounds,*gen));
        fill_n(back_inserter(params),policy[i]->getNumBasisFunctions(),0);

    }
    
    delete gen;
    
   vector<BoundsPair> allBounds ( params.size(),parBounds );
   CRADLE *cr = new CRADLE(allBounds,par);
   //cr->setObserver ( obs );
   alg = cr;
   

    cout << "number of features: " << params.size() << endl;
}

const action_t *agent_start ( const observation_t *this_observation ) {

    if ( !ended )
        agent_end ( 0. ); //apparently this does not get called every time
    ended = false;

    stateFile.open ( "state.txt" );

    totalReward = 0;

    if(alg->hasConverged())
	params = alg->getBestPoint();
    else
      params = alg->nextPoint();
	
     //check bounds, some algorithms may go beyond
     for(int i=0,size=params.size(); i<size; ++i) {
	if(params[i] < parBounds.lowerBound())
	  params[i] = parBounds.lowerBound();
	if(params[i] > parBounds.upperBound())
	  params[i] = parBounds.upperBound();
      }


    applyPolicy (this_observation);

    /* In a real action you might want to store the last observation and last action*/
    replaceRLStruct ( &this_action, &last_action );
    replaceRLStruct ( this_observation, last_observation );

    return &this_action;
}

const action_t *agent_step ( double reward, const observation_t *this_observation ) {

    totalReward+= reward;

    applyPolicy (this_observation);


    /* In a real action you might want to store the last observation and last action*/
    replaceRLStruct ( &this_action, &last_action );
    replaceRLStruct ( this_observation, last_observation );

    return &this_action;
}

void agent_end ( double reward ) {

    totalReward +=reward;



        alg->functionComputed ( params,-totalReward );  //we minimize

        //copy best point into vector.txt
        ofstream pointFile("vector.txt");
        ostream_iterator<double> outtstream(pointFile, " ");
        vector<double> curBest = alg->getBestPoint();
        copy(curBest.begin(),curBest.end(),outtstream);
        pointFile.close();


    ended = true;

    stateFile.close();

    clearRLStruct ( &last_action );
    clearRLStruct ( last_observation );
}

void agent_cleanup() {

    delete alg;

    clearRLStruct ( &this_action );
    clearRLStruct ( &last_action );
    freeRLStructPointer ( last_observation );
}

const char* agent_message ( const char* inMessage ) {
	string message ( inMessage );

	if ( message == "reset" )  {
		delete alg;
		alg = NULL;
		params.assign(params.size(),0);
		return "done";
	} else if ( message == "episode cut" ) {
		agent_end ( 0. );
		return "";
	}

    return "I don't know how to respond to your message";
}



void loadParameters() {
	ifstream paramFile("cradleParams.txt");
	
	if(paramFile.eof())
		throw runtime_error("cannot access parameter file");
	
	
	paramFile >> par.populSize >> par.lastListLenght >> par.minLDelta;
	cout << "population size: " << par.populSize << " last size: " << 
				par.lastListLenght << " min last delta: " 
				<< par.minLDelta << endl;
	
	paramFile.close();
}


void  applyPolicy (const observation_t *obs ) {
	
    vector<double> observations(&obs->doubleArray[0],&obs->doubleArray[obs->numDoubles]);

#if EVALUATE_POLICY
    params = fromFile;
#endif

    for(int i=0; i<this_action.numDoubles; ++i) {

        int numFeatures = params.size()/this_action.numDoubles;


        vector<double> theta(params.begin()+(numFeatures*i),params.begin()+(numFeatures*(i+1)));


        double f = policy[i]->value(theta,observations);

        f = std::max(std::min(f,actBounds[i].upperBound()),actBounds[i].lowerBound());

        this_action.doubleArray[i] = f;

#if EVALUATE_POLICY
        stateFile 	<< f << " ";
#endif
    }

#if EVALUATE_POLICY
//print observations
    for(int i=0; i<last_observation->numDoubles; ++i)
        stateFile << last_observation->doubleArray[i] << " ";

    stateFile << endl;
#endif
}