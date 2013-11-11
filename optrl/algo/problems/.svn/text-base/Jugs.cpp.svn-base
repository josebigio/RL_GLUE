#include "Jugs.h"

#include <cmath>
#include <vector>

#include "ProblemStore.h"

using namespace std;

namespace pargo {

ProblemStore ps_Jugs(new pargo::JugsProblem());

int JugsProblem::getn() const {
	return 2;
}

double JugsProblem::computef ( const std::vector<double>& x ) const {
	return sin ( x[0] ) + ( x[1]*x[1] ) + sin(2 *x[0]);
}

std::vector<BoundsPair> JugsProblem::getBounds() const {
	return vector<BoundsPair>(getn(),make_pair(-4*M_PI,4*M_PI));
}

std::string JugsProblem::getName() const {
	return "Jugs";
}


}
