#ifndef pargo_MPIOptimizer_h__guard
#define pargo_MPIOptimizer_h__guard


namespace pargo {

class Poll;
class Problem;
	
unsigned long run_mpi_master(Poll *poll,unsigned long maxEvaluations);


void run_mpi_slave(const Problem *problem);


}

#endif
