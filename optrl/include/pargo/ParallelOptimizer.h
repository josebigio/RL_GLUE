#ifndef pargo_ParallelOptimizer_h__guard
#define pargo_ParallelOptimizer_h__guard


#include <pargo/Optimizer.h>

#include <pargo/PointValuePair.h>

#include <list>

namespace pargo {

class ParallelOptimizer : public Optimizer {
public:
  
  ParallelOptimizer(unsigned int maxThreadNumber);

  unsigned long run(const Problem* problem, Poll *poll,unsigned long maxEvaluations);
  
private:
  unsigned int maxThreadNumber;
  
};

}

#endif
