#ifndef pargo_Bohachevsky3Problem_h__guard
#define pargo_Bohachevsky3Problem_h__guard

#include <pargo/Problem.h>

namespace pargo {

struct  Bohachevsky3Problem : public Problem {

	int getn() const;

	double computef ( const std::vector<double>& x ) const;

	std::vector<BoundsPair> getBounds() const;

};

}

#endif
