//from R. Fletcher and M. J. D. Powell. A rapidly convergent descent method for minimization. Computer Journal, (6):163-168, 1963.
//bounds from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#include "PowellProblem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Powell("Powell",new pargo::PowellProblem());

using namespace std;

int PowellProblem::getn() const {
	return 4;
}

double PowellProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	return pow(x[0]+10*x[1],2)+5*pow(x[2]-x[3],2)+pow(x[1]-2*x[2],4)+10*pow(x[0]-x[3],4);
}

std::vector<BoundsPair> PowellProblem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(-4.,5.) );
}

}
