#ifndef pargo_BealeProblem_h__guard
#define pargo_BealeProblem_h__guard

#include <pargo/Problem.h>

namespace pargo {

struct  BealeProblem : public Problem {

	int getn() const;

	double computef ( const std::vector<double>& x ) const;

	std::vector<BoundsPair> getBounds() const;

};

}

#endif
