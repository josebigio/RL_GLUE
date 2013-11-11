#ifndef pargo_JugsProblem_h__guard
#define pargo_JugsProblem_h__guard

#include <pargo/Problem.h>

namespace pargo {
	
	struct  JugsProblem : public Problem {
		
		int getn() const;
		
		double computef ( const std::vector<double>& x ) const;
		
		std::vector<BoundsPair> getBounds() const;

		std::string getName() const;
		
	};
	
}

#endif