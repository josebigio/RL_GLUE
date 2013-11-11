//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#include "ColvilleProblem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Colville("Colville",new pargo::ColvilleProblem());

using namespace std;

int ColvilleProblem::getn() const {
	return 4;
}

double ColvilleProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	return 100*pow(pow(x[0],2)-x[1],2)+pow(x[0]-1,2)+pow(x[2]-1,2)+90*pow(pow(x[2],2)-x[3],2)+10.1*(pow(x[1]-1,2)+pow(x[3]-1,2))+19.8*(x[1]-1)*(x[3]-1);
}

std::vector<BoundsPair> ColvilleProblem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(-10.,10.) );
}

}
