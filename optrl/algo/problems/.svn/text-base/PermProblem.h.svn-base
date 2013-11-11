//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#ifndef pargo_PermProblem_h__guard
#define pargo_PermProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  PermProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double b = 0.5;
		double s_out = 0;
		for (int k=1;k<=var_num;++k){
			double s_in = 0;
    		for (int j=0;j<var_num;++j){
        		s_in = s_in+(pow(j+1,k)+b)*(pow(x[j]/(j+1),k)-1);
    		}
    		s_out = s_out+pow(s_in,2);
		}
		return s_out;
    }

    std::vector<BoundsPair> getBounds() const {
		double b = (double)var_num;
		return std::vector<BoundsPair>(getn(),std::make_pair(-b,b) );
	}

};

}

#endif
