//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#include "EasomProblem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Easom("Easom",new pargo::EasomProblem());

using namespace std;

int EasomProblem::getn() const {
	return 2;
}

double EasomProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	return -cos(x[0])*cos(x[1])*exp(-pow(x[0]-M_PI,2)-pow(x[1]-M_PI,2));
}

std::vector<BoundsPair> EasomProblem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(-100.,100.) );
}

}
