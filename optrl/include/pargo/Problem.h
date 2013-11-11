#ifndef pargo_Problem_h__guard
#define pargo_Problem_h__guard

#include <pargo/BoundsPair.h>

#include <vector>
#include <string>

namespace pargo {

struct Problem {

	virtual double computef ( const std::vector<double>& xin ) const = 0;

	virtual int getn() const = 0;
	
	virtual std::vector<BoundsPair> getBounds() const =0;

	virtual std::string getName() const {
		return "UnknownProblem";
	}

	virtual ~Problem();
};

}

#endif

