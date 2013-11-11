#ifndef pargo_GlobalFastPoll_h__guard
#define pargo_GlobalFastPoll_h__guard

#include <pargo/Poll.h>
#include <pargo/BoundsPair.h>
#include <pargo/PointValuePair.h>

#include <vector>
#include <valarray>
#include <set>
#include <list>
#include <iosfwd>

namespace pargo {

class Problem;

struct GlobalFastPollParams {

    GlobalFastPollParams() :
        populSize(100),
        lastListLenght(25),
        minDelta(1e-6),
        minLDelta(1e-2) {}

    unsigned int populSize, lastListLenght;
    double minDelta, minLDelta;
};

class GlobalFastPoll : public Poll {
public:

    typedef GlobalFastPollParams ParamType;

    GlobalFastPoll(const std::vector<BoundsPair> & bounds, const ParamType par = ParamType());

    bool hasConverged() const;

    double getBestValue() const;
    std::vector<double> getBestPoint() const;
	std::vector<double> randomPoint() const;


    std::vector<double> nextPoint();
	
	double getRadius();
	std::vector<double> getCentre(unsigned int n);
	
	void saveTo( std::ostream& );
	
	void readFrom( std::istream& );


    typedef std::vector< ValarrayValuePair > PopulationType;


private:

    ParamType par;
    unsigned int probDim, pointsOut;
    std::valarray<double>lower_bounds, upper_bounds;
    PopulationType population;
    std::list<ValarrayValuePair> lastPoints;
    double delta, deltaInit,worstValue;
    bool best3Changed, tooManyAttempts;

    void doFunctionComputed(const std::vector<double>& , double value);
	
	std::valarray<double> computeWeights(const std::set<PopulationType::const_iterator>& );
	void updateLast(const ValarrayValuePair& point);
    std::set<GlobalFastPoll::PopulationType::const_iterator> createFamilySet();
    void keepPoint(const ValarrayValuePair& point);
    std::vector<double> initialDistribution();
    std::valarray<double> controlledRandomPoint();
    bool isPointValid(std::valarray<double>& point) const;
    std::valarray<double> pointFromBestThree();

//
// 	PopulationType population;
//
//     PopulationType::iterator idxmax, idxmin;
//     double delta, deltaInit, minDelta;
//     std::vector<BoundsPair> bounds;
//
// 	//statistics
// 	unsigned long long timesPointAccepted, timesBestChanged, timesInitialPopulation;
// 	VectorValuePair initialBest;
//
// 	void doFunctionComputed(const std::vector<double>& , double value);
//     std::vector<double>  computeFamilyStepPoint(const int size);
//     int computedFamilyStepFunction( const std::vector<double>& newPoint, double fNewPoint);
// 	void prepareForFamily();
// 	std::vector<double> randomPoint() const;
// 	bool isPointValid(const std::vector<double>& point) const;
//
// 	std::set< PopulationType::const_iterator > createFamilySet (int);
};

}

#endif // RandomGlobalPoll2_h
