//from Lucidi, S., Piccioni, M.: Random tunneling by means of acceptance-rejection sampling for global optimization. J. Optim. Theory Appl. 62(2), 255–279 (1989)

#include "SixHumpCamelbackProblem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_SixHumpCamelback("SixHumpCamelback",new pargo::SixHumpCamelbackProblem());

using namespace std;

int SixHumpCamelbackProblem::getn() const {
	return 2;
}

double SixHumpCamelbackProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	return (4-2.1*pow(x[0],2)+pow(x[0],4)/3.)*pow(x[0],2)+x[0]*x[1]+(-4+4*pow(x[1],2))*pow(x[1],2);
}

std::vector<BoundsPair> SixHumpCamelbackProblem::getBounds() const {
	vector<BoundsPair> vec;
	vec.push_back(make_pair(-3.,3.));
	vec.push_back(make_pair(-2.,2.));
	return vec;
}

}
