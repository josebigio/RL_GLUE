#include <iostream>
#include <pargo/RandomGlobalPoll.h>
#include <pargo/LineSearchPoll.h>

#include <pargo/MPIOptimizer.h>
#include <pargo/Problem.h>
#include <pargo/obs/GnuplotObserver.h>

#include "problems/ProblemStore.h"

#include <mpi.h>

#include <vector>

#include <stdlib.h>
#include <time.h>

#include <cmath>

#include <stdexcept>


using namespace std;
using namespace pargo;


// algorithm settings
unsigned long functionEvaluationsBudget = 1000000;
//int populationSize = 500;
double minimumDelta = 1e-6;
// end algorithm settings


void run_master ( const Problem *, string& );

int main() {
try{
	srand ( time ( NULL ) );

	MPI::Init();

	//per farne uno decommenta questo e commenta il resto
		string name = "p10nLocMin_2";
	 	Problem * prob = ProblemStore::getProblemByName(name);
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
}
catch (std::runtime_error& er) {
	cout << er.what() << endl;
}
		return 0;
	}

	void run_master ( const Problem *prob, string& name ) {

		int dim=prob->getn()*25;
		//int dim=populationSize;
		double minDelta = minimumDelta;

		pargo::RandomGlobalPoll *poll;
		poll = new pargo::RandomGlobalPoll ( dim,prob->getBounds(),minDelta );

		string nome_obs = "points_";
		GnuplotObserver obs ( nome_obs+name+".txt" );
		poll->setObserver ( obs );

// 	vector<double> initial(prob->getn(),0);
// 	poll = new LineSearchPoll(initial,prob->computef(initial));

		//cout << "Family step prints:" << endl;

		double t1 = MPI_Wtime();

		unsigned long maxIter = functionEvaluationsBudget;

		unsigned long count = run_mpi_master ( poll,maxIter );

		double total = MPI_Wtime() - t1;

		cout << endl;
		cout << "Random Global Poll" << endl;
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
		cout << "      population size: " << dim << endl;
		cout << "   -- statistics" << endl;
		cout << "      number of function evaluations: " << poll->getTimesInitialPopulation() << endl;
		cout << "      delta: " << poll->getInitialDelta() << endl;
		cout << "      best point: " ;
		for ( int i=0; i<prob->getn(); ++i ) {
			cout << poll->getInitialBestPoint() [i] << " ";
		}
		cout << endl;
		cout << "      best value: " << poll->getInitialBestValue();
		cout << endl << endl;


		cout << "-- main phase: controlled random search" << endl;
		cout << "   -- settings" << endl;
		cout << "      minimum delta: " << minDelta << endl;
		cout << "   -- statistics" << endl;
		cout << "      number of function evaluations: " << count-poll->getTimesInitialPopulation() << endl;
		cout << "      delta: " << poll->getDelta() << endl;
		cout << "      best point: " ;
		for ( int i=0; i<prob->getn(); ++i ) {
			cout << poll->getBestPoint() [i] << " ";
		}
		cout << endl;
		cout << "      best value: " << poll->getBestValue() << endl;
		cout << "      times a new point was accepted: " << poll->getTimesPointAccepted() << endl;
		cout << "      times the best point was changed: " << poll->getTimesBestChanged() << endl;
		cout << endl;

		cout << "-- final statistics" << endl;
		std::cout << "   total elapsed time: " << total << " seconds" << std::endl;
		cout << "   total number of function evaluations: " << count << endl;
		cout << endl;

		delete poll;

	}




