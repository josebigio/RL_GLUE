//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#ifndef pargo_SumSquaresProblem_h__guard
#define pargo_SumSquaresProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  SumSquaresProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double s = 0;
		for (int j=0;j<var_num;++j){
		    s = s + (j+1)*pow(x[j],2); 
		}
		return s;
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-10.0,10.0) );
	}

};

}

#endif
