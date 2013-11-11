//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm
//WRONG VERSION

#ifndef pargo_SchwefelProblem_h__guard
#define pargo_SchwefelProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  SchwefelProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double s = 0;
		for (int i=0;i<var_num;++i){
			s = s -x[i]*sin(sqrt(fabs(x[i])));
		}
		return 418.9829*var_num+s;
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-500.0,500.0) );
	}

};

}

#endif
