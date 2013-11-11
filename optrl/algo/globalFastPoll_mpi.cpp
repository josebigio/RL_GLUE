#include <iostream>
#include <pargo/GlobalFastPoll.h>

#include <pargo/MPIOptimizer.h>
#include <pargo/Problem.h>
#include <pargo/obs/GnuplotObserver.h>

#include "problems/ShipProblem.h"
#include "problems/ShipProblem.h"

#include <mpi.h>

#include <vector>

#include <stdlib.h>
#include <time.h>

#include <cmath>

#include <stdexcept>
#include <fstream>


using namespace std;
using namespace pargo;


// algorithm settings
unsigned long functionEvaluationsBudget = 1000000;
//int populationSize = 500;
double minimumDelta = 1e-2;
// end algorithm settings


void run_master ( const Problem *, string& );

int main() {
    try {
        srand ( time ( NULL ) );
		
		cout << "Starting" << endl;

        MPI::Init();

        //per farne uno decommenta questo e commenta il resto
         string name = "Ship";
//         Problem * prob = ProblemStore::getProblemByName(name);
		Problem * prob = new ShipProblem();
        //fino a qui

        //per farli tutti decommenta questo e commenta il resto
        //map<string,Problem*> allProblems =  ProblemStore::getAllProblems();
        //map<string,Problem*>::iterator probIt = allProblems.begin();

        //for ( ; probIt != allProblems.end(); ++probIt ) {

        //	string name = probIt->first;

        //	Problem *prob = probIt->second;
        //fino a qui

        if ( MPI::COMM_WORLD.Get_rank() == 0 ) {
            run_master ( prob, name );
        } else
            run_mpi_slave ( prob );

        MPI_Barrier(MPI_COMM_WORLD);

        //per farli tutti decommenta questo e commenta il resto
        //}
        //fino a qui

        MPI::Finalize();

        delete prob;
    }
    catch (std::runtime_error& er) {
        cout << er.what() << endl;
    }
    return 0;
}

void run_master ( const Problem *prob, string& name ) {

    GlobalFastPoll::ParamType p;
	
	p.populSize = prob->getn() * 25;
	p.lastListLenght = prob->getn() * 12;
	p.minLDelta = minimumDelta;

    GlobalFastPoll poll(prob->getBounds(),p);

    string nome_obs = "points_";
    GnuplotObserver obs ( nome_obs+name+".txt" );
    poll.setObserver ( obs );
	
	ifstream initialFile("initialPoints.txt");
	poll.readFrom(initialFile);
	initialFile.close();

// 	vector<double> initial(prob->getn(),0);
// 	poll = new LineSearchPoll(initial,prob->computef(initial));

    //cout << "Family step prints:" << endl;

    double t1 = MPI_Wtime();

    unsigned long maxIter = functionEvaluationsBudget;

    unsigned long count = run_mpi_master ( &poll,maxIter );

    double total = MPI_Wtime() - t1;

    cout << endl;
    cout << "Global Fast Poll" << endl;
    cout << "-- problem: " << name << endl;
    cout << "   dimension: " << prob->getn() << endl;

    cout << endl;
    cout << "-- general configuration" << endl;
    cout << "   function evaluations budget: " << maxIter << endl;
    int s;
    cout << "   number of parallel processes: " << ( MPI_Comm_size ( MPI_COMM_WORLD,&s ),s ) << endl;
    cout << endl;

    cout << "-- initial phase: create population" << endl;
    cout << "   -- settings" << endl;
    cout << "      population size: " << p.populSize << endl;
  

    cout << "-- main phase: controlled random search" << endl;
    cout << "      best point: " ;
    for ( int i=0; i<prob->getn(); ++i ) {
        cout << poll.getBestPoint() [i] << " ";
    }
    cout << endl;
    cout << "      best value: " << poll.getBestValue() << endl;

    cout << "-- final statistics" << endl;
    std::cout << "   total elapsed time: " << total << " seconds" << std::endl;
    cout << "   total number of function evaluations: " << count << endl;
    cout << endl;

}




