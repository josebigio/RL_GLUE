//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#ifndef pargo_AckleyProblem_h__guard
#define pargo_AckleyProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

#include <iostream>

namespace pargo {

template <unsigned int var_num>
struct  AckleyProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
        double a = 20;
        double b = 0.2;
        double c = 2*M_PI;
        double s1 = 0;
        double s2 = 0;
        for (int i=0; i<var_num; ++i) {
            s1 = s1+pow(x[i],2);
            s2 = s2+cos(c*x[i]);
        }
        return -a*exp(-b*sqrt(1./var_num*s1))-exp(1./var_num*s2)+a+exp(1.);
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-15.,30.) );
	}

};

}

#endif
