#ifndef pargo_Hartmann3Problem_h__guard
#define pargo_Hartmann3Problem_h__guard

#include <pargo/Problem.h>

namespace pargo {

struct  Hartmann3Problem : public Problem {

	int getn() const;

	double computef ( const std::vector<double>& x ) const;

	std::vector<BoundsPair> getBounds() const;

};

}

#endif
