#include "MultiModalGaussianProblem.h"

#include <boost/math/distributions/normal.hpp>

using namespace boost::math;
using namespace pargo;
using namespace std;

int MultiModalGaussianProblem::getn() const {
return 2;
}

double MultiModalGaussianProblem::computef(const std::vector<double>& x ) const {
	normal_distribution<double> x0_1(3,1);
	normal_distribution<double> x1_1(3,9);
	
	normal_distribution<double> x0_2(7,9);
	normal_distribution<double> x1_2(7,1);
	
	normal_distribution<double> x0_3(1.5,.5);
	normal_distribution<double> x1_3(8.5,.5);
	
	return -(	1 * pdf(x0_1,x[0]) * pdf(x1_1,x[1]) + 1 * pdf(x0_2,x[0]) * pdf(x1_2,x[1]) + 
			0.6 * pdf(x0_3,x[0]) * pdf(x1_3,x[1])); 
}


std::vector<BoundsPair> MultiModalGaussianProblem::getBounds() const {
		return vector<BoundsPair>(getn(),make_pair(-20.,20.)); 
}



/*
function r = rewardEval(p)

Mu(:,1)=[3;3]; Mu(:,2)=[7;7]; Mu(:,3)=[1.5;8.5];
Sigma(:,:,1)=diag([1,9]); Sigma(:,:,2)=diag([9,1]); Sigma(:,:,3)=diag([.5,.5]);
Priors = [1 1 0.6];
Priors = Priors/sum(Priors);
r = zeros(size(p,2),1);
r_max = 0;
for i=1:size(Mu,2)
  r = r + Priors(i) * gaussPDF(p,Mu(:,i),Sigma(:,:,i));
  r_max = r_max + Priors(i) * gaussPDF(Mu(:,i),Mu(:,i),Sigma(:,:,i));
end
%Rescaling (not obligatory)
r = r'/r_max;
*/
