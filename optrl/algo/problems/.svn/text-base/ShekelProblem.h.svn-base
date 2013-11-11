//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#ifndef pargo_ShekelProblem_h__guard
#define pargo_ShekelProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int param_m>
struct  ShekelProblem : public Problem {

    int getn() const {
        return 4;
    }

    double computef ( const std::vector<double>& x ) const {
		double a[4][10];
		a[0][0]=4; a[0][1]=1; a[0][2]=8; a[0][3]=6; a[0][4]=3; a[0][5]=2; a[0][6]=5; a[0][7]=8; a[0][8]=6; a[0][9]=7;
		a[1][0]=4; a[1][1]=1; a[1][2]=8; a[1][3]=6; a[1][4]=7; a[1][5]=9; a[1][6]=5; a[1][7]=1; a[1][8]=2; a[1][9]=3.6;
		a[2][0]=4; a[2][1]=1; a[2][2]=8; a[2][3]=6; a[2][4]=3; a[2][5]=2; a[2][6]=3; a[2][7]=8; a[2][8]=6; a[2][9]=7;
		a[3][0]=4; a[3][1]=1; a[3][2]=8; a[3][3]=6; a[3][4]=7; a[3][5]=9; a[3][6]=3; a[3][7]=1; a[3][8]=2; a[3][9]=3.6;
		double c[10];
		c[0]=0.1; c[1]=0.2; c[2]=0.2; c[3]=0.4; c[4]=0.4; c[5]=0.6; c[6]=0.3; c[7]=0.7; c[8]=0.5; c[9]=0.5;
		double s = 0;
		for (int j=1;j<=param_m;++j){
   			double p = 0;
   			for (int i=1;i<=4;++i){
      			p = p + pow(x[i-1]-a[i-1][j-1],2);
   			}
   			s = s + 1/(p+c[j-1]);
		}
		return -s;
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(0.0,10.0) );
	}

};

}

#endif
