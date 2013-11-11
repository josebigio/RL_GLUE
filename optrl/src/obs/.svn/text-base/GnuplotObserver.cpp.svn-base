#include <pargo/obs/GnuplotObserver.h>

#include <iterator>
#include <algorithm>

using namespace std;

namespace pargo {

GnuplotObserver::GnuplotObserver(const std::string filePath) : file(filePath.c_str()) {}


void GnuplotObserver::functionComputed(const std::vector< double >& point, double value) {

	file << value << " ";
	
	ostream_iterator<double> oit(file," ");
	
	copy(point.begin(), point.end(), oit);
	
	file << endl;
	
}

GnuplotObserver::~GnuplotObserver() {
	file.close();
}

}

