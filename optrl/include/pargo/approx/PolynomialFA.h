#ifndef pargo_PolynomialFA_h__guard
#define pargo_PolynomialFA_h__guard

#include <pargo/approx/LinearFA.h>

#include <vector>

namespace pargo {

struct PolynomialFA : public LinearFA {

	PolynomialFA(unsigned int nvars, unsigned int degree) : degree(degree), nvars(nvars) {}

	unsigned int getNumBasisFunctions() const;
	
	std::vector<double> computeFeatures ( const std::vector<double>& observations ) const;


private:
	
	int increment_indices ( std::vector< int >& indices, int pos ) const;

	unsigned int degree,nvars;

};



}

#endif
