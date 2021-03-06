#ifndef pargo_CRADLE_h__guard
#define pargo_CRADLE_h__guard

#include <pargo/Poll.h>
// #include <pargo/BoundsPair.h>
#include <pargo/GlobalFastPoll.h>

#include <valarray>
#include <vector>

namespace pargo {


class CRADLE : public Poll {
public:

    typedef GlobalFastPollParams ParamType;

    CRADLE(const std::vector<BoundsPair> & bounds, const ParamType par = ParamType());

    bool hasConverged() const;

    double getBestValue() const;
    std::vector<double> getBestPoint() const;

    std::vector<double> nextPoint();

// 	void saveTo( std::ostream& );
// 	
	void readPointsFrom( std::istream& );
	
	~CRADLE();


private:
	
	void doFunctionComputed(const std::vector<double>& , double value);
	
	enum Phase {
		global,
		transition,
		local
	};

    ParamType par;
	GlobalFastPoll * firstAlgorithm;
	Poll *secondAlgorithm;
	std::valarray<double> centre;
	std::vector<BoundsPair> bounds;
	Phase phase;
   
};

}

#endif // RandomGlobalPoll2_h
