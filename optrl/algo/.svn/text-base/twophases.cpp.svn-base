#include <iostream>
#include <pargo/RandomGlobalPoll.h>
#include <pargo/LineSearchPoll.h>

#include <pargo/SequentialOptimizer.h>
#include <pargo/ParallelOptimizer.h>

#include "problems/QuadraticProblem.h"
#include "problems/MultiModalGaussianProblem.h"



#include <vector>

#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace pargo;

int main() {
    srand ( time(NULL) );

    double sum = 0;
    double steps = 0;
    int rounds = 1;

	MultiModalGaussianProblem prob; // QuadraticProblem();

	ParallelOptimizer parallel(3);
	
    for(int i=0; i<rounds; ++i) {

        int dim=80;
        double delta = 0.001;

        RandomGlobalPoll global(dim,prob.getBounds(),delta);

        unsigned long count = parallel.run(&prob,&global,100);

        vector<double> initial = global.getBestPoint();

		LineSearchPoll::ParamType p;
		p.minStep = 1e-10;
		p.gamma = 1e-50;
        LineSearchPoll local(initial, prob.computef(initial),p);

        count += parallel.run(&prob,&local,1000);

//     cout << "best point:" << endl;
//
//     for (int i=0; i<prob->getn(); ++i) {
//         cout << poll->getBestPoint()[i] << " \t \t";
//     }

//     cout << endl;
//     cout << "f best:" << poll->getBestValue() << endl;
//     cout << "f count=" << count << endl;

        sum += local.getBestValue();
        steps += static_cast<double>(count)/rounds;

    }

    cout << "mean: " << sum/rounds << " steps: " << steps <<  endl;

    return 0;
}
