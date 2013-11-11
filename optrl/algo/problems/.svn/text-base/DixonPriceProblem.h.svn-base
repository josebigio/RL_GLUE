//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#ifndef pargo_DixonPriceProblem_h__guard
#define pargo_DixonPriceProblem_h__guard

#include <pargo/Problem.h>

#include <cmath>

namespace pargo {


template <unsigned int var_num>
struct  DixonPriceProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
        double s1 = 0;
        for (int j=2; j<=var_num; ++j) {
            s1 = s1+j*pow(2*pow(x[j-1],2)-x[j-2],2);
        }
        return 	s1+pow(x[0]-1,2);
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(), std::make_pair(-10.,10.) );
	}

};

}

#endif
