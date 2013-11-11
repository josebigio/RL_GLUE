//from R. Fletcher and M. J. D. Powell. A rapidly convergent descent method for minimization. Computer Journal, (6):163-168, 1963.

#ifndef pargo_FletcherPowellProblem_h__guard
#define pargo_FletcherPowellProblem_h__guard

#include <pargo/Problem.h>

 #include <cmath>
#include <vector>

#include <sstream>

namespace pargo {

template <unsigned int var_num>
struct  FletcherPowellProblem : public Problem {

    int getn() const {
        return var_num;
    }

    double computef ( const std::vector<double>& x ) const {
		double a[var_num];
		double b[var_num];
		double alpha[var_num];
		for (int i=0; i<var_num; ++i) {
            double k=(double) i;
			a[i]=(k/var_num)*200-100;
            k=(double) 2*i;
			b[i]=(k/(2*var_num))*200-100;
			k=(double) (var_num-i);
			alpha[i]=(k/var_num)*2*M_PI-M_PI;
        }
		double S=0;
        for (int j=0; j<var_num; ++j) {
			double A=0;
			double B=0;
        	for (int i=0; i<var_num; ++i) {
            	A = A+a[j]*sin(x[i])+b[j]*cos(x[i]);
            	B = B+a[j]*sin(alpha[i])+b[j]*cos(alpha[i]);
        	}
			S=S+pow(B-A,2);
		}
        return S;
    }

    std::vector<BoundsPair> getBounds() const {
		return std::vector<BoundsPair>(getn(),std::make_pair(-M_PI,M_PI) );
	}
	
	std::string getName() const {
		std::stringstream s;
		s << "FletcherPowell_"  << var_num;
		return s.str(); 
	}

};

}

#endif
