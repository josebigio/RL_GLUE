#include <iostream>



#include <pargo/LineSearchPoll.h>
#include <pargo/MPIOptimizer.h>

#include <pargo/Problem.h>
#include <pargo/obs/GnuplotObserver.h>


#include "problems/ProblemStore.h"

#include <mpi.h>

#include <vector>

#include <stdlib.h>
#include <time.h>


using namespace std;
using namespace pargo;


void run_master(const Problem *);

void run_slave(const Problem *);

int main() {
    srand ( time(NULL) );

	Problem * prob = ProblemStore::getProblemByName("QuadraticProblem");

    MPI::Init();


    if(MPI::COMM_WORLD.Get_rank() == 0) {
        run_master(prob);
    }
    else
        run_mpi_slave(prob);


    MPI::Finalize();

    delete prob;

    return 0;
}

void run_master(const Problem *prob) {

	
	vector<double> initial(prob->getn(),0);
	initial[0] = 10;
	initial[1] = 10;

	LineSearchPoll::ParamType p;
	p.minStep = 1e-10;
	p.initialStep = 1;
	p.gamma = 1e-50;
    pargo::LineSearchPoll *poll = new pargo::LineSearchPoll(initial,prob->computef(initial),p);

//	GnuplotObserver obs("points.txt");
//	poll->setObserver(obs);

// 	vector<double> initial(prob->getn(),0);
// 	poll = new LineSearchPoll(initial,prob->computef(initial));

    //cout << "Family step prints:" << endl;

    double t1 = MPI_Wtime();
	
	unsigned long maxIter = 10000;
	
    unsigned long count = run_mpi_master(poll,maxIter);
	
    double total = MPI_Wtime() - t1;

	cout << endl;
	cout << "Linea Search Poll" << endl;
	
	cout << endl;
	cout << "-- general configuration" << endl;
    cout << "      best point: " ;
    for (int i=0; i<prob->getn(); ++i) {
        cout << poll->getBestPoint()[i] << " ";
    }
    cout << endl;
    cout << "      best value: " << poll->getBestValue() << endl;

	cout << "-- final statistics" << endl;
    std::cout << "   total elapsed time: " << total << " seconds" << std::endl;
    cout << "   total number of function evaluations: " << count << endl;	
    cout << endl;

    delete poll;

}




