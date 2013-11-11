//from Breiman, L., Cutler, A.: Deterministic algorithm for global optimization. Math. Program. 58, 179–199 (1993)

#ifndef pargo_CosMixProblem_h__guard
#define pargo_CosMixProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  CosMixProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double f = 0.0;
		for (int i=0;i<var_num;++i){
			f = f + 0.1*cos(5.0*M_PI*x[i])-pow(x[i],2);
		}
        return -f;
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-1.,1.) );
	}

};

}

#endif
