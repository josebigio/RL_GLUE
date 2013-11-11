//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#ifndef pargo_LevyProblem_h__guard
#define pargo_LevyProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  LevyProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double z[var_num];
		for (int i=0;i<var_num;++i){
			z[i] = 1+(x[i]-1)/4;
		}
		double s = pow(sin(M_PI*z[0]),2);
		for (int i=0;i<var_num-1;++i){
		    s = s+pow(z[i]-1,2)*(1+10*pow(sin(M_PI*z[i]+1),2));
		}
		return s+pow(z[var_num-1]-1,2)*(1+pow(sin(2*M_PI*z[var_num-1]),2));
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-10.,10.) );
	}

};

}

#endif
