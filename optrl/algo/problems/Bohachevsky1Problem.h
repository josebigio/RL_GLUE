#ifndef pargo_Bohachevsky1Problem_h__guard
#define pargo_Bohachevsky1Problem_h__guard

#include <pargo/Problem.h>

namespace pargo {

struct  Bohachevsky1Problem : public Problem {

	int getn() const;

	double computef ( const std::vector<double>& x ) const;

	std::vector<BoundsPair> getBounds() const;

};

}

#endif
