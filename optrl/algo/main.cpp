
#include <pargo/SequentialOptimizer.h>

#include <pargo/GlobalFastPoll.h>
#include <pargo/LocalCSMADPoll.h>

#include <pargo/obs/GnuplotObserver.h>

#include "problems/ProblemStore.h"

#include <pargo/Problem.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace pargo;

int main() {
    //srand ( time ( NULL ) );


    Problem &prob = ProblemStore::getProblemByName("Jugs");


    GlobalFastPoll::ParamType gp;
    gp.populSize = 25*prob.getn();
    gp.lastListLenght = 2*prob.getn();
    gp.minDelta = 1e-1;
    gp.minLDelta = 1;

    GnuplotObserver obs ( "pointsJiao.txt" );

    const int numSteps = 1000;
    const int numTrials = 500;

    for(int i=0; i<numTrials; ++i) {

        GlobalFastPoll poll(prob.getBounds(),gp);

        poll.setObserver ( obs );

        SequentialOptimizer opt;
        unsigned long count = 0;
        count = opt.run ( &prob,&poll,numSteps);

//         vector<double> best = poll.getBestPoint();
//         double bestV = poll.getBestValue();
// 
//         LocalCSMADPoll::ParamType p;
//         p.initialStep = poll.getRadius();
//         p.minStep = p.initialStep*1e-2;
// 
//         LocalCSMADPoll locPol(prob.getBounds(),best,bestV,p);
//         locPol.setObserver(obs);
// 
//         count += opt.run(&prob,&locPol,numSteps - count);

        for(; count < numSteps; ++count)
            obs.functionComputed(poll.getBestPoint(),poll.getBestValue());

    }


//     vector<double> bestPoint = poll.getBestPoint();
//
//     cout << "best point:" << endl;
//
//     for ( int i=0; i<prob.getn(); ++i ) {
//         cout << bestPoint[i] << " ";
//     }
//
//     cout << endl;
//     cout << "f best: " << poll.getBestValue() << endl;
// // 	cout << "radius: " << poll.getRadius() << endl;
//     cout << "f count=" << count << endl;

    /*

    RandomGlobalPoll poll2(gp.populSize, prob.getBounds(), gp.minDelta);

    //     LocalSifonePoll::ParamType lp;
    //     lp.initialStep =  poll.getRadius();
    //     lp.minStep = lp.initialStep*1e-3;
    //
    // 	LocalSifonePoll poll2(prob.getBounds(),bestPoint,bestV,lp);
    //     poll2.setObserver(obs);
    //
    count += opt.run ( &prob,&poll2,1000000);

    bestPoint = poll2.getBestPoint();

    cout << "best point:" << endl;

    for ( int i=0; i<prob.getn(); ++i ) {
        cout << bestPoint[i] << " ";
    }

    cout << endl;
    cout << "f best:" << poll2.getBestValue() << endl;
    cout << "f count=" << count << endl;*/

    return 0;
}
