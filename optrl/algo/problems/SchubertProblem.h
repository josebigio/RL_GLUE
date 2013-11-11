#ifndef pargo_SchubertProblem_h__guard
#define pargo_SchubertProblem_h__guard

#include <pargo/Problem.h>

namespace pargo {

struct  SchubertProblem : public Problem {

	int getn() const;

	double computef ( const std::vector<double>& x ) const;

	std::vector<BoundsPair> getBounds() const;

};

}

#endif
