#ifndef pargo_SequentialOptimizer_h__guard
#define pargo_SequentialOptimizer_h__guard


#include <pargo/Optimizer.h>

namespace pargo {

struct SequentialOptimizer : public Optimizer {

  unsigned long run(const Problem* problem, Poll *poll,unsigned long maxEvaluations);
  
};

}

#endif
