#include <pargo/RandomGlobalPoll.h>

#include <iostream>


#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <limits>

using namespace std;

namespace pargo {


RandomGlobalPoll::RandomGlobalPoll ( const int dim, const std::vector<BoundsPair> & bounds, double minDelta ) :
    dimPopul ( dim ),
    population(),
    idxmax(),
    idxmin(),
    delta ( 0 ),
    deltaInit ( 0 ),
    minDelta(minDelta),
    bounds(bounds),
    timesPointAccepted(0),
    timesBestChanged(0),
    timesInitialPopulation(0),
    initialBest(make_pair(vector<double>(),0.)) {
	}

bool RandomGlobalPoll::hasConverged() const {
    return population.size() >= dimPopul && delta < minDelta;
}

vector<double> RandomGlobalPoll::randomPoint() const {

    vector<double> point;

    for ( int i=0, size = bounds.size(); i<size; ++i ) {
        double span = bounds[i].upperBound() - bounds[i].lowerBound();
        point.push_back ( rand() * ( span /RAND_MAX ) + bounds[i].lowerBound() );
    }

    return point;
}

std::set<RandomGlobalPoll::PopulationType::const_iterator>
RandomGlobalPoll::createFamilySet ( int size )  {

    std::set<RandomGlobalPoll::PopulationType::const_iterator> idxFamily;

    double coeff= static_cast<double> ( dimPopul ) /RAND_MAX;

    while ( idxFamily.size() <size ) {

        int valIdx= static_cast<int> ( rand() *coeff );

        if ( valIdx==dimPopul ) valIdx--;

        RandomGlobalPoll::PopulationType::const_iterator chosen = population.begin();
        advance ( chosen, valIdx );
        idxFamily.insert ( chosen );

    }

    return idxFamily;
}

struct PopulationIteratorLess {

    bool operator() ( const RandomGlobalPoll::PopulationType::const_iterator& a,const RandomGlobalPoll::PopulationType::const_iterator& b ) {
        return a->value() < b->value();
    }

};

struct EtaGenerator {
    double fmin;
    double phi;

    EtaGenerator ( double fmin, double phi ) :
        fmin ( fmin ),
        phi ( phi ) {}

    double operator() ( const RandomGlobalPoll::PopulationType::const_iterator& idx ) {
		double eta = idx->value() - fmin + phi;
		if(eta == 0)
			eta = numeric_limits<double>::epsilon(); //avoid division by zero
        return 1./eta;
    }

};

struct WeightGenerator {
    double sumEta;

    explicit WeightGenerator ( double sum ) : sumEta ( sum ) {}

    double operator() ( double eta ) {
        return eta/sumEta;
    }

};

static vector<double> createCentroid ( const set<RandomGlobalPoll::PopulationType::const_iterator>& idxFamily,
                                       const std::vector<double>& weight ) {

    set<RandomGlobalPoll::PopulationType::const_iterator>::const_iterator itIdxFamily=idxFamily.begin();

    std::vector<double> centroid ( ( *itIdxFamily )->point().size(), 0 );

    std::vector<double>::const_iterator itWeight =  weight.begin();

    for ( ; itIdxFamily != idxFamily.end(); ++itIdxFamily, ++itWeight )
        for ( int i=0; i< ( *itIdxFamily )->point().size(); ++i )
            centroid[i] += ( ( *itIdxFamily )->point() ) [i] * ( *itWeight );


    return centroid;
}

static double computeSumFWeights ( const set<RandomGlobalPoll::PopulationType::const_iterator>& idxFamily,
                                   const std::vector<double>& weight ) {
    double sumFWeights = 0;
    set<RandomGlobalPoll::PopulationType::const_iterator>::const_iterator itIdxFamily =idxFamily.begin();
    std::vector<double>::const_iterator itWeight =  weight.begin();
    for ( ; itIdxFamily != idxFamily.end(); ++itIdxFamily, ++itWeight )
        sumFWeights += ( *itIdxFamily )->value() * ( *itWeight );

    return sumFWeights;
}

static vector<double> computeNewPoint ( const vector<double>& centroid,
                                        double alpha,
                                        const vector<double>& maxPoint ) {
// compute new point
    std::vector<double> newPoint;
    for ( int i=0, size = centroid.size(); i<size; ++i ) {
        double val = centroid[i] - alpha* ( maxPoint[i]-centroid[i] );
        newPoint.push_back ( val );
    }

    return newPoint;
}

bool RandomGlobalPoll::isPointValid ( const vector<double>& point ) const {

    for ( int i=0, size = point.size(); i < size; ++i )
        if ( 	point[i] != point[i] ||
				point[i] < bounds[i].lowerBound() ||
				point[i] > bounds[i].upperBound() )
            return false;

    return true;
}

std::vector<double> RandomGlobalPoll::computeFamilyStepPoint ( const int size ) {

    std::vector<double> newPoint;
    do {

        // create family index set
        set<RandomGlobalPoll::PopulationType::const_iterator>  idxFamily = createFamilySet ( size );

        // find max idx in family
        RandomGlobalPoll::PopulationType::const_iterator idxmaxFam= *max_element (	idxFamily.begin(),
                idxFamily.end(),
                PopulationIteratorLess() );

        // compute centroid family
// 		cout << "deltaInit: " << deltaInit << " delta: " << delta << endl;

        double phi = bounds.size()*delta*delta/deltaInit;

        std::vector<double> eta;

        transform ( idxFamily.begin(), idxFamily.end(),back_inserter ( eta ),
                    EtaGenerator ( idxmin->value(),phi ) );


        double sumEta = accumulate ( eta.begin(),eta.end(),0. );


        // compute weights
        std::vector<double> weight;
        transform ( eta.begin(),eta.end(),back_inserter ( weight ),WeightGenerator ( sumEta ) );


        // compute centroid
        std::vector<double> centroid = createCentroid ( idxFamily,weight );



        // compute new point (reflex max idx in family with centroid family)
        // compute stepsize
        double sumFWeights = computeSumFWeights ( idxFamily,weight );

        double alpha = 1 - ( idxmaxFam->value() - sumFWeights ) / ( delta+phi );

        // compute new point
        newPoint =  computeNewPoint ( centroid,alpha,idxmaxFam->point() );



    } while ( !isPointValid ( newPoint ) );

    return newPoint;
}

int RandomGlobalPoll::computedFamilyStepFunction ( const std::vector<double>& newPoint,
        double fNewPoint ) {

// 	cout << "f popul max before " << idxmax->value() << endl;

    if ( fNewPoint < idxmax->value() ) {

        ++timesPointAccepted;


        ( *idxmax ) = make_pair ( newPoint, fNewPoint );

        if ( fNewPoint < idxmin->value() ) {
            ++timesBestChanged;
            idxmin = idxmax;
        }

        idxmax = max_element ( population.begin(), population.end() );

// 		cout << "f popul max after " << idxmax->value() << endl;
// 		cout << "f popul min " << idxmin->value() << endl;


        delta = idxmax->value() - idxmin->value();

        return 0;
    }
    return 1;
}



std::vector<double> RandomGlobalPoll::nextPoint() {

	if(hasConverged())
		return min_element ( population.begin(),population.end() )->point();
	
    if ( population.size() < dimPopul ) {
        ++timesInitialPopulation;
        return randomPoint();
    }

    return computeFamilyStepPoint ( std::min ( bounds.size()+1,population.size()-1 ) );

}

void RandomGlobalPoll::doFunctionComputed ( const std::vector<double>& point, double value ) {

	if(hasConverged())
		return;

    if ( population.size() < dimPopul ) {
        population.push_back ( make_pair ( point, value ) );
        if ( population.size() == dimPopul )
            prepareForFamily();
    } else
        computedFamilyStepFunction ( point, value );
}

void RandomGlobalPoll::prepareForFamily() {

    idxmin = min_element ( population.begin(),population.end() );
    idxmax = max_element ( population.begin(),population.end() );

    initialBest = *idxmin;

    delta = idxmax->value()  - idxmin->value();
    deltaInit = delta;
}


void RandomGlobalPoll::setPopulation ( const std::vector< std::pair< std::vector<double>, double > >& newPopul ) {

    population.assign ( newPopul.begin(),newPopul.end() );

    if ( population.size() >= dimPopul )
        prepareForFamily();

}

double RandomGlobalPoll::getBestValue() const {
    if(population.empty())
        throw runtime_error("Called getBestValue() before computing any point value");

    return min_element ( population.begin(),population.end() )->value();

}

std::vector<double> RandomGlobalPoll::getBestPoint() const {
    if(population.empty())
        throw runtime_error("Called getBestPoint() before computing any point value");

    return min_element ( population.begin(),population.end() )->point();
}

double RandomGlobalPoll::getInitialDelta() const {
    if(population.size() < dimPopul)
        throw runtime_error("called getInitialDelta() before completing the population");

    return deltaInit;
}

unsigned long long RandomGlobalPoll::getTimesPointAccepted() const {
    if(population.size() < dimPopul)
        throw runtime_error("called getTimesPointAccepted() before completing the population");

    return timesPointAccepted;
}

unsigned long long RandomGlobalPoll::getTimesBestChanged() const {
    if(population.size() < dimPopul)
        throw runtime_error("called getTimesBestChanged() before completing the population");


    return timesBestChanged;
}

unsigned long long RandomGlobalPoll::getTimesInitialPopulation() const {
    if(population.size() < dimPopul)
        throw runtime_error("called getTimesInitialPopulation() before completing the population");


    return timesInitialPopulation;
}

std::vector<double> RandomGlobalPoll::getInitialBestPoint() const {
    if(population.size() < dimPopul)
        throw runtime_error("called getInitialBestPoint() before completing the population");

    return initialBest.point();
}

double RandomGlobalPoll::getInitialBestValue() const {
    if(population.size() < dimPopul)
        throw runtime_error("called getInitialBestValue() before completing the population");

    return initialBest.value();
}


}

