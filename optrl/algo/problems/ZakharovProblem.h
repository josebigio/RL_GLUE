//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#ifndef pargo_ZakharovProblem_h__guard
#define pargo_ZakharovProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  ZakharovProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double s1 = 0;
		double s2 = 0;
		for (int j=0;j<var_num;++j){
		    s1 = s1 + pow(x[j],2);
    		s2 = s2 + 0.5*(j+1)*x[j];
		}
		return s1+pow(s2,2)+pow(s2,4);
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-5.0,10.0) );
	}

};

}

#endif
