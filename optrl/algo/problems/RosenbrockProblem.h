//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#ifndef pargo_RosenbrockProblem_h__guard
#define pargo_RosenbrockProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  RosenbrockProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double s = 0;
		for (int j=0;j<var_num-1;++j){
		    s = s + 100*pow(pow(x[j],2)-x[j+1],2)+pow(x[j]-1,2);
		}
		return s;
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-5.0,10.0) );
	}

};

}

#endif
