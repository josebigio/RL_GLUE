//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#ifndef pargo_GriewankProblem_h__guard
#define pargo_GriewankProblem_h__guard

#include <pargo/Problem.h>

#include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  GriewankProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {

        double fr = 4000;
        double s = 0;
        double p = 1;
        for (int j=1; j<=var_num; ++j) s = s+pow(x[j-1],2);
        for (int j=1; j<=var_num; ++j) p = p*cos(x[j-1]/sqrt(j));
        return s/fr-p+1;
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-600.,600.) );
	}

};

}

#endif
