#include <pargo/SequentialOptimizer.h>

#include <pargo/Poll.h>
#include <pargo/Problem.h>

#include <vector>

using namespace std;
 
namespace pargo {
  
unsigned long SequentialOptimizer::run(	const Problem* problem, 
								Poll *poll,
								unsigned long maxEvaluations) {
  
  unsigned long evaluations = 0;
  for(; !poll->hasConverged() &&  evaluations < maxEvaluations ; ++evaluations) {
	vector<double> point = poll->nextPoint();
	poll->functionComputed(point,problem->computef(point));
  }
  
  return evaluations;
  
}
  
  
}
