#ifndef pargo_PollObserver_h__guard
#define pargo_PollObserver_h__guard


#include <vector>

namespace pargo {
	

struct PollObserver {

	virtual void functionComputed(const std::vector<double>& , double value) = 0;
	
	virtual ~PollObserver() {};
};

}

#endif
