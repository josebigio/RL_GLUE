//from Lucidi, S., Piccioni, M.: Random tunneling by means of acceptance-rejection sampling for global optimization. J. Optim. Theory Appl. 62(2), 255–279 (1989)

#include "SchubertPenalized1Problem.h"

#include <limits>
#include <math.h>

#include "ProblemStore.h"

namespace pargo {

	ProblemStore ps_SchubertPenalized1("SchubertPenalized1",new pargo::SchubertPenalized1Problem());

using namespace std;

int SchubertPenalized1Problem::getn() const {
	return 2;
}

double SchubertPenalized1Problem::computef ( const std::vector<double>& x ) const {
//   static int count = 0;
// 	std::cout << "valutazione " << ++count << std::endl;
	double F1, F2;
	F1=0;
	F2=0;
	for (int I=1;I<=5;++I){
		F1=F1+I*cos((I+1.0)*x[0]+I);
		F2=F2+I*cos((I+1.0)*x[1]+I);
	}
	double F=F1*F2;
	return F+(pow(x[0]+1.42513,2)+pow(x[1]+0.80032,2))/2.0;
}

std::vector<BoundsPair> SchubertPenalized1Problem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(-10.,10.) );
}

}
