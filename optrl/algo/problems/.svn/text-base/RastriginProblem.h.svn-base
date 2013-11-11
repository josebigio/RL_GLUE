//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#ifndef pargo_RastriginProblem_h__guard
#define pargo_RastriginProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  RastriginProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double s = 0;
		for (int j=0;j<var_num;++j){
			s = s+(pow(x[j],2)-10*cos(2*M_PI*x[j]));
		}
		return 10*var_num+s;
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-5.12,5.12) );
	}

};

}

#endif
