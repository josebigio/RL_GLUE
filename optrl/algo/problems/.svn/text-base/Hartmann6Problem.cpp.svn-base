//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#include "Hartmann6Problem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Hartmann6("Hartmann6",new pargo::Hartmann6Problem());

using namespace std;

int Hartmann6Problem::getn() const {
	return 6;
}

double Hartmann6Problem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	double a[4][6], c[4], p[4][6];
	a[0][0]=10.0;	a[0][1]=3.0;	a[0][2]=17.0;	a[0][3]=3.5;	a[0][4]=1.7;	a[0][5]=8.0;
	a[1][0]=0.05;	a[1][1]=10.0;	a[1][2]=17.0;	a[1][3]=0.1;	a[1][4]=8.0;	a[1][5]=14.0;
	a[2][0]=3.0;	a[2][1]=3.5;	a[2][2]=1.7;	a[2][3]=10.0;	a[2][4]=17.0;	a[2][5]=8.0;
	a[3][0]=17.0;	a[3][1]=8.0;	a[3][2]=0.05;	a[3][3]=10.0;	a[3][4]=0.1;	a[3][5]=14.0;
	c[0]=1.0;c[1]=1.2;c[2]=3.0;c[3]=3.2;
	p[0][0]=0.1312;	p[0][1]=0.1696;	p[0][2]=0.5569;	p[0][3]=0.0124;	p[0][4]=0.8283;	p[0][5]=0.5886;
	p[1][0]=0.2329;	p[1][1]=0.4135;	p[1][2]=0.8307;	p[1][3]=0.3736;	p[1][4]=0.1004;	p[1][5]=0.9991;
	p[2][0]=0.2348;	p[2][1]=0.1451;	p[2][2]=0.3522;	p[2][3]=0.2883;	p[2][4]=0.3047;	p[2][5]=0.6650;
	p[3][0]=0.4047;	p[3][1]=0.8828;	p[3][2]=0.8732;	p[3][3]=0.5743;	p[3][4]=0.1091;	p[3][5]=0.0381;
	double s = 0;
	for (int i=0;i<4;++i){
		double sm=0;
		for (int j=0;j<6;++j){
			sm=sm+a[i][j]*pow(x[j]-p[i][j],2);
   		}
		s=s+c[i]*exp(-sm);
	}
	return -s;
}

std::vector<BoundsPair> Hartmann6Problem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(0.,1.) );
}

}
