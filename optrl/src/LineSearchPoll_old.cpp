#include <pargo/LineSearchPoll.h>

#include <algorithm>
#include <iostream>

using namespace std;

namespace pargo  {

int LineSearchPoll::k() {
	return dir % bestPoint.size();
}

int LineSearchPoll::ksign() {
	return ( dir < bestPoint.size() ) ? 1 : -1;
}

LineSearchPoll::LineSearchPoll ( const std::vector<double>& initial,
								 double initValue,
								 double minStep,
								 double delta,
								 double theta,
								 double gamma
							   ) : bestPoint ( initial ),
		centre ( initial ),
		last(),
		candidate ( initial ),
		alpha ( 2*initial.size(),1 ),
		bestValue ( initValue ),
		candValue ( initValue ),
		delta ( delta ),
		theta ( theta ),
		alpha_p ( 0 ),
		centreValue ( initValue ),
		gamma ( gamma ),
		minStep ( minStep ),
		dir ( 0 ),
		expansion ( false ) {}


std::vector<double> LineSearchPoll::nextPoint() {

	if ( hasConverged() )
		return bestPoint;

	if ( expansion )
		alpha_p *= delta;
	else {
		alpha_p = alpha[dir];
	}

	last = centre;
	last[k() ] = centre[k() ] + ksign() *alpha_p ;
	return last;
}


void LineSearchPoll::functionComputed (const std::vector<double>& , double value ) {

	if ( hasConverged() )
		return;

//   cout << value << " ";
//   for(int i=0; i<last.size(); ++i)
// 	cout << last[i] << " ";
//   cout << endl;

//    bool condition = (value - centreValue) <= (-gamma * alpha_p * alpha_p);
	bool condition = ( ( value - centreValue ) <= ( -gamma * alpha_p * alpha_p ) &&
					   ( value < bestValue ) ); // la condizione è verificata solo se il punto ha valore migliore di bestPoint

	if ( value < bestValue ) {
		bestPoint = last;
		bestValue = value;
	}

	if ( expansion && condition ) {
		//cout << "exp cond" << endl;
		alpha[dir] = alpha_p;
		candidate = last;
		candValue = value;
	}
	if ( !expansion && !condition ) {
		//cout << "no exp no cond" << endl;
		alpha[dir] *= theta;
		//candidate = centre;
		//candValue = centreValue;
		dir = ( dir + 1 ) % ( 2*bestPoint.size() );
	}
	if ( expansion && !condition ) {
		//cout << "exp no cond" << endl;
		expansion = false;
		centre = candidate;
		centreValue = candValue;
		dir = ( dir + 1 ) % ( 2*bestPoint.size() );
	}
	if ( !expansion && condition ) {
		//cout << "no exp cond" << endl;
		alpha[dir] = alpha_p;
		candidate = last;
		candValue = value;
		expansion = true;
	}


}


bool LineSearchPoll::hasConverged() const {
	double max = *std::max_element ( alpha.begin(), alpha.end() );
	return max < minStep;
}

double LineSearchPoll::getBestValue() const {
	return bestValue;
}
std::vector<double> LineSearchPoll::getBestPoint() const {
	return bestPoint;
}


}


