//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#ifndef pargo_MichalewicsProblem_h__guard
#define pargo_MichalewicsProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  MichalewicsProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double m = 10;
		double s = 0;
		for (int i=0;i<var_num;++i){
			s = s+sin(x[i])*pow(sin((i+1)*pow(x[i],2)/M_PI),2*m);
		}
		return -s;
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(0.,M_PI) );
	}

};

}

#endif
