//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#include "BoothProblem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Booth("Booth",new pargo::BoothProblem());

using namespace std;

int BoothProblem::getn() const {
	return 2;
}

double BoothProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	return pow(x[0]+2*x[1]-7,2)+pow(2*x[0]+x[1]-5,2);
}

std::vector<BoundsPair> BoothProblem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(-10.,10.) );
}

}
