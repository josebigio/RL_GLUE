#include <pargo/LocalCSMADPoll.h>



using namespace std;
using namespace pargo;

int main() {
	
	ShipProblem ship;
	
	LocalCSMADPoll::ParamType params;
	
	params.initialStep = 1;
	params.minStep = 1e-4;
	params.sigma = 0.5;
	
	LocalCSMADPoll poll();
	
	
	SequentialOptimizer opt;
    unsigned long count = 0;
    count = opt.run ( &prob,&poll,numSteps);
	
}