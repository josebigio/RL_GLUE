//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#include "SchubertProblem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Schubert("Schubert",new pargo::SchubertProblem());

using namespace std;

int SchubertProblem::getn() const {
	return 2;
}

double SchubertProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	double F1, F2;
	F1=0;
	F2=0;
	for (int I=1;I<=5;++I){
		F1=F1+I*cos((I+1.0)*x[0]+I);
		F2=F2+I*cos((I+1.0)*x[1]+I);
	}
	return F1*F2;
}

std::vector<BoundsPair> SchubertProblem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(-10.,10.) );
}

}
