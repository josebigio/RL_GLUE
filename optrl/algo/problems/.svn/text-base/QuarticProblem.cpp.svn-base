//from Lucidi, S., Piccioni, M.: Random tunneling by means of acceptance-rejection sampling for global optimization. J. Optim. Theory Appl. 62(2), 255–279 (1989)

#include "QuarticProblem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Quartic("Quartic",new pargo::QuarticProblem());

using namespace std;

int QuarticProblem::getn() const {
	return 2;
}

double QuarticProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	return (1./4.)*pow(x[0],4)-(1./2.)*pow(x[0],2)+.1*x[0]+(1./2.)*pow(x[1],2);
}

std::vector<BoundsPair> QuarticProblem::getBounds() const {
	return vector<BoundsPair>(getn(),make_pair(-10.0,10.0) );
}

}
