

//deprecated and not compiled

//substituted by the tamplate

#include <pargo/PointValuePair.h>

namespace pargo {



PointValuePair::PointValuePair ( const std::pair<std::vector<double>, double>& pointPair ) :
		pointPair ( pointPair ) {}

std::vector<double>& PointValuePair::point() const {
	pointPair.first;
}

double PointValuePair::value() const {
	return pointPair.second;
}

PointValuePair::operator std::pair<std::vector<double>, double>() const {
	return pointPair;
}

PointValuePair::operator std::pair<std::vector<double>, double>&() {
	return pointPair;
}

bool operator< ( const PointValuePair &a, const  PointValuePair&b ) {
	return a.value() < b.value();
}

}
