//from Törn, A., Zilinskas, A.: Global Optimization. Springer, Berlin (1989)

#include "TreccaniProblem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Treccani("Treccani",new pargo::TreccaniProblem());

using namespace std;

int TreccaniProblem::getn() const {
	return 2;
}

double TreccaniProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	double X1Q = x[0]*x[0];
	return X1Q*X1Q+4.0*X1Q*x[0]+4.0*X1Q+x[1]*x[1];
}

std::vector<BoundsPair> TreccaniProblem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(-2.5,2.5) );
}

}
