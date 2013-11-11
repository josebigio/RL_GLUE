#include "QuadraticProblem.h"

#include <pargo/BoundsPair.h>

#include <limits>


#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Quadratic("Quadratic",new pargo::QuadraticProblem());

using namespace std;

int QuadraticProblem::getn() const {
	return 2;
}

double QuadraticProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;

	return x[0]*x[0]+x[1]*x[1]-2*x[0]+3*x[1];
}


std::vector<BoundsPair> QuadraticProblem::getBounds() const { 
	return vector<BoundsPair>(getn(),make_pair(-20.,20.));
}

}
