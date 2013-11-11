//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#include "Hartmann3Problem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Hartmann3("Hartmann3",new pargo::Hartmann3Problem());

using namespace std;

int Hartmann3Problem::getn() const {
	return 3;
}

double Hartmann3Problem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	double a[4][3];
	for (int i=0;i<4;++i){
		a[i][1]=10.0;
	}
	for (int j=0;j<2;++j){
		a[2*j][0]=3.0; a[2*j+1][0]=0.1; 
		a[2*j][2]=30.0; a[2*j+1][2]=35.0; 
	}
	double c[4];
	c[0]=1.0;c[1]=1.2;c[2]=3.0;c[3]=3.2;
	double p[4][3];
	p[0][0]=0.36890;p[0][1]=0.11700;p[0][2]=0.26730;
	p[1][0]=0.46990;p[1][1]=0.43870;p[1][2]=0.74700;
	p[2][0]=0.10910;p[2][1]=0.87320;p[2][2]=0.55470;
	p[3][0]=0.03815;p[3][1]=0.57430;p[3][2]=0.88280;
	double s = 0;
	for (int i=0;i<4;++i){
		double sm=0;
		for (int j=0;j<3;++j){
			sm=sm+a[i][j]*pow(x[j]-p[i][j],2);
   		}
		s=s+c[i]*exp(-sm);
	}
	return -s;
}

std::vector<BoundsPair> Hartmann3Problem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(0.,1.) );
}

}
