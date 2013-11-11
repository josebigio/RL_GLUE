#ifndef pargo_GoldsteinPriceProblem_h__guard
#define pargo_GoldsteinPriceProblem_h__guard

#include <pargo/Problem.h>

namespace pargo {

struct  GoldsteinPriceProblem : public Problem {

	int getn() const;

	double computef ( const std::vector<double>& x ) const;

	std::vector<BoundsPair> getBounds() const;

};

}

#endif
