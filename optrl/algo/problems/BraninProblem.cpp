//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#include "BraninProblem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Branin("Branin",new pargo::BraninProblem());

using namespace std;

int BraninProblem::getn() const {
	return 2;
}

double BraninProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	return pow(x[1]-(5.1/(4*pow(M_PI,2)))*pow(x[0],2)+5*x[0]/M_PI-6,2)+10*(1-1/(8*M_PI))*cos(x[0])+10;
}

std::vector<BoundsPair> BraninProblem::getBounds() const {
  vector<BoundsPair> vec;
  vec.insert (vec.begin(),make_pair(-5.,10.));
  vec.insert (vec.begin()+1,make_pair(0.,15.));
  return vec;
}

}
