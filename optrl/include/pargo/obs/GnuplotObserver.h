#ifndef pargo_GnuplotObserver_h__guard
#define pargo_GnuplotObserver_h__guard

#include <pargo/PollObserver.h>

#include <iostream>
#include <fstream>

namespace pargo {

class GnuplotObserver : public pargo::PollObserver {
	
public:
	GnuplotObserver(const std::string filePath);

	void functionComputed(const std::vector<double>& , double value);
	
    ~GnuplotObserver();
	
private:
	
	std::ofstream file;
	
};

}


#endif
