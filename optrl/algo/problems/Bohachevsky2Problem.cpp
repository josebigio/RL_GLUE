//from http://www-optima.amp.i.kyoto-u.ac.jp/member/student/hedar/Hedar_files/TestGO_files/Page364.htm

#include "Bohachevsky2Problem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_Bohachevsky2("Bohachevsky2",new pargo::Bohachevsky2Problem());

using namespace std;

int Bohachevsky2Problem::getn() const {
	return 2;
}

double Bohachevsky2Problem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	return pow(x[0],2)+2*pow(x[1],2)-0.3*cos(3*M_PI*x[0])*cos(4*M_PI*x[1])+0.3;
}

std::vector<BoundsPair> Bohachevsky2Problem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(-100.,100.) );
}

}
