//from Lucidi, S., Piccioni, M.: Random tunneling by means of acceptance-rejection sampling for global optimization. J. Optim. Theory Appl. 62(2), 255–279 (1989)

#ifndef pargo_p15nLocMinProblem_h__guard
#define pargo_p15nLocMinProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

namespace pargo {

template <unsigned int var_num>
struct  p15nLocMinProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double PG=acos(-1.0);
		double COST=0.1;
		double NM=var_num-1;
		double F=pow(sin(3.0*PG*x[0]),2);

		for (int I=1;I<=NM;++I){
			F=F+(pow(x[I-1]-1.0,2))*(1.0+pow(sin(3.0*PG*x[I]),2));
		}
		F=F+(pow(x[var_num-1]-1.0,2))*(1.0+pow(sin(2.0*PG*x[var_num-1]),2));
		return COST*F;
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-5.,5.) );
	}

};

}

#endif
