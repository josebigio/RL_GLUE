//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#include "HumpProblem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Hump("Hump",new pargo::HumpProblem());

using namespace std;

int HumpProblem::getn() const {
	return 2;
}

double HumpProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	return 1.0316285+4*pow(x[0],2)-2.1*pow(x[0],4)+pow(x[0],6)/3+x[0]*x[1]-4*pow(x[1],2)+4*pow(x[1],4);
}

std::vector<BoundsPair> HumpProblem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(-5.,5.) );
}

}
