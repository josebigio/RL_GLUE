//from Pintér, J.D.: Global Optimization in Action, Continuous and Lipschitz Optimization: Algorithms, Implementations and Applications. Nonconvex Optimization and Its Applications, vol. 6. Kluwer Academic, Dordrecht (1996)

#ifndef pargo_PinterProblem_h__guard
#define pargo_PinterProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  PinterProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double XSTAR[var_num];
		double b = (double) var_num;
		for (int I=1;I<=var_num;++I){
			double a = (double) I;
			if (I % 2 == 0){
				XSTAR[I-1] = (a/b)*4.0-0.5;
			} else {
				XSTAR[I-1] = -(a/b)*4.0+0.5;
			}
		}
		double F = 0.0;
		for (int I=1;I<=var_num;++I){
			F = F+0.025*b*pow(x[I-1]-XSTAR[I-1],2);
		}
		double P1 = 0.0;
		double P2 = 0.0;
		for (int I=1;I<=var_num;++I){
			P1 = P1 + (x[I-1]-XSTAR[I-1]) + pow(x[I-1]-XSTAR[I-1],2);
			P2 = P2 + (x[I-1]-XSTAR[I-1]);
		}
		return F+pow(sin(P1),2)+pow(sin(P2),2);
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-5.,5.) );
	}

};

}

#endif
