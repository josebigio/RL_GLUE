//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#include "GoldsteinPriceProblem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_GoldsteinPrice("GoldsteinPrice",new pargo::GoldsteinPriceProblem());

using namespace std;

int GoldsteinPriceProblem::getn() const {
	return 2;
}

double GoldsteinPriceProblem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	double a = 1+pow(x[0]+x[1]+1,2)*(19-14*x[0]+3*pow(x[0],2)-14*x[1]+6*x[0]*x[1]+3*pow(x[1],2));
	double b = 30+pow(2*x[0]-3*x[1],2)*(18-32*x[0]+12*pow(x[0],2)+48*x[1]-36*x[0]*x[1]+27*pow(x[1],2));
	return a*b;
}

std::vector<BoundsPair> GoldsteinPriceProblem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(-2.,2.) );
}

}
