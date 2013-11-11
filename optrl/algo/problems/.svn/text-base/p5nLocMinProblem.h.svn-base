//from Lucidi, S., Piccioni, M.: Random tunneling by means of acceptance-rejection sampling for global optimization. J. Optim. Theory Appl. 62(2), 255–279 (1989)

#ifndef pargo_p5nLocMinProblem_h__guard
#define pargo_p5nLocMinProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  p5nLocMinProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double PG=acos(-1.0);
		double CT=25.e-2;
		double RK=10.0;
		double RA=1.0;
		double NM=var_num-1;
		double F=RK*pow(sin(PG*(1.0+CT*(x[0]-1.0))),2);

		for (int I=1;I<=NM;++I){
			F=F+(pow((1.0+CT*(x[I-1]-1.0))-RA,2))*(1.0+RK*pow(sin(PG*(1.0+CT*(x[I]-1.0))),2));
		}
		F=F+pow((1.0+CT*(x[var_num-1]-1.0))-RA,2);
		return (PG/var_num)*F;
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-10.,10.) );
	}

};

}

#endif
