#ifndef pargo_PointValuePair_h__guard
#define pargo_PointValuePair_h__guard

#include <vector>
#include <valarray>

namespace pargo {


template <typename PointClass>
class PointValuePair {

	std::pair<PointClass, double> pointPair;

public:

	PointValuePair ( const std::pair<PointClass, double>& pointPair ) :
		pointPair ( pointPair ) {}

	const PointClass& point() const {
		return pointPair.first;
	}

	PointClass& point()  {
		return pointPair.first;
	}

	double value() const {
		return pointPair.second;
	}

	operator std::pair<PointClass, double>() const {
		return pointPair;
	}

	operator std::pair<PointClass, double>&() {
		return pointPair;
	}

};

typedef PointValuePair<std::vector<double> > VectorValuePair;
typedef PointValuePair<std::valarray<double> >  ValarrayValuePair;

template <typename T>
bool operator< ( const PointValuePair<T> & a, const  PointValuePair<T>& b ) {
	return a.value() < b.value();
}

}

#endif
