//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#include "MatyasProblem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Matyas("Matyas",new pargo::MatyasProblem());

using namespace std;

int MatyasProblem::getn() const {
	return 2;
}

double MatyasProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	return 0.26*(pow(x[0],2)+pow(x[1],2))-0.48*x[0]*x[1];
}

std::vector<BoundsPair> MatyasProblem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(-10.,10.) );
}

}
