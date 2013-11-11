#ifndef pargo_LineSearchPoll_h__guard
#define pargo_LineSearchPoll_h__guard

#include <pargo/Poll.h>
#include <pargo/PointValuePair.h>

#include <vector>
#include <valarray>
#include <set>
#include <map>

namespace pargo {

struct ValarrayLess {
    bool operator()(const std::valarray<double>&, const std::valarray<double>&);
};

struct LineSearchPollParams {

    LineSearchPollParams() :
        minStep(1e-3),
        initialStep(1),
        gamma(1e-6),
        delta(2),
        theta(0.5) {}

    double minStep,initialStep,gamma,delta,theta;
};

class  LineSearchPoll : public Poll {
public:

    typedef LineSearchPollParams ParamType;

    LineSearchPoll(const std::vector<double>& initial, double initValue,
                   const LineSearchPoll::ParamType& p = LineSearchPoll::ParamType());

    LineSearchPoll(const std::vector<double>& initial, double initValue,
                   const std::vector< std::vector<double> >& directions,
                   const LineSearchPoll::ParamType& p = LineSearchPoll::ParamType());

    std::vector<double> nextPoint();

    bool hasConverged() const;

    double getBestValue() const;
    std::vector<double> getBestPoint() const;

	std::vector<double> getCentre() const;
	double getCentreValue() const;
private:

    int k();
    int ksign();
	
	void doFunctionComputed(const std::vector<double>& ,double value);
	
    void moveCentre(const ValarrayValuePair& lastPoint,  bool expansion, const std::valarray<double>& , double);

	bool testConditionOn(double value, double alpha_p);
	
    int phase;

    std::set<std::valarray<double>, ValarrayLess > activePoints;
	std::set<std::valarray<double>, ValarrayLess > converged;
    std::map<std::valarray<double>, double, ValarrayLess> alpha;
	std::map<std::valarray<double>, double, ValarrayLess> minAlpha;

    LineSearchPoll::ParamType p;

    ValarrayValuePair bestPoint, centre,bestClose;
    unsigned int dir,ring,dirBase;
};
}

#endif
