//from Breiman, L., Cutler, A.: Deterministic algorithm for global optimization. Math. Program. 58, 179–199 (1993)

#ifndef pargo_EsponProblem_h__guard
#define pargo_EsponProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  EsponProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double F1 = 0.0;
		for (int i=0;i<var_num;++i){
			F1 = F1 + pow(x[i],2);
		}
        return -exp(-0.5*F1);
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-1.,1.) );
	}

};

}

#endif
