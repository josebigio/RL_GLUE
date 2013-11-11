//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#ifndef pargo_TridProblem_h__guard
#define pargo_TridProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  TridProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double s1 = 0;
		double s2 = 0;
		for (int j=0;j<var_num;++j){
		    s1 = s1 + pow(x[j]-1,2);    
		}
		for (int j=1;j<var_num;++j){
		    s2 = s2 + x[j]*x[j-1];
		}
		return s1-s2;
    }

    std::vector<BoundsPair> getBounds() const {
		double b = (double) var_num;
		b=pow(b,2);
		return std::vector<BoundsPair>(getn(),std::make_pair(-b,b) );
	}

};

}

#endif
