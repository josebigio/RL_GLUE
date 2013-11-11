#include <pargo/JiaoPoll.h>

#include <numeric>

#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <stdexcept>

using namespace std;

namespace pargo {

struct PopulationIteratorLess {

	bool operator()(const JiaoPoll::PopulationType::const_iterator& a,const JiaoPoll::PopulationType::const_iterator& b) {
		return a->value() < b->value();
	}

};


JiaoPoll::JiaoPoll(const std::vector<BoundsPair> & bounds, const ParamType par) :
	par(par),
	probDim(bounds.size()),
	pointsOut(0),
	lower_bounds(bounds.size()),
	upper_bounds(bounds.size()),
	population(),
	delta(0.),
	deltaInit(0.),
	worstValue(0.),
	best3Changed(false),
	tooManyAttempts(false) {

	population.reserve(par.populSize);

	std::vector<BoundsPair>::const_iterator it = bounds.begin();
	for(int j = 0; it != bounds.end(); ++it, ++j) {
		lower_bounds[j] = it->lowerBound();
		upper_bounds[j] = it->upperBound();
	}
}

vector<double>  JiaoPoll::nextPoint() {

	if(pointsOut < par.populSize)
		return initialDistribution();

	if(population.size() == 0)    //argh, no population point has arrived yet!
		return randomPoint();

	if(delta < par.minDelta)
		return getBestPoint(); //converged, eta may become infinite

	valarray<double> point(probDim);
	if(best3Changed) {
		point = pointFromBestThree();
		best3Changed = false;
		if(isPointValid(point))
			return vector<double> (&point[0], (&point[0]) +point.size());
	}

	tooManyAttempts = false;
	int count = 0;
	do {

		point =  controlledRandomPoint();

		++count;
		tooManyAttempts = count > 10;

		if(count >= 50) {
			//force validity
			//it is unlikely, but it may happen if the population is not much bigger than
			//the domain dimensions
			point[point < lower_bounds] = lower_bounds[point < lower_bounds];
			point[point > upper_bounds] = upper_bounds[point > upper_bounds];
		}

	} while(!isPointValid(point));

	return vector<double> (&point[0], (&point[0]) +point.size());

}

valarray<double> JiaoPoll::pointFromBestThree() {

	PopulationType& p = population; //short name

	valarray<double> x_q_num = ((p[1].point() * p[1].point() - p[2].point() *p[2].point()) *
								p[0].value() + (p[2].point() *p[2].point()-p[0].point() *p[0].point()) *
								p[1].value() + (p[0].point() *p[0].point() - p[1].point() *p[1].point()) *
								p[2].value());

	valarray<double> x_q_den = (p[1].point()-p[2].point()) *p[0].value() + (p[2].point()-p[0].point()) *p[1].value()
							   + (p[0].point()-p[1].point()) *p[2].value();

//     if ( ( x_q_den >= 1e-6 ).sum() == x_q_den.size() )
	return (1./2) * x_q_num / x_q_den;

//     return valarray<double> ( probDim+1 ); //a non-valid point according to isPointValid()
}

bool JiaoPoll::isPointValid(std::valarray<double>& point) const {

	if(point.size() != probDim)
		return false;

// 		cout << "-- point validity " << endl;
// 	for(int i=0; i<point.size(); ++i)
// 		cout << point[i] << " ";
// 	cout << endl;

	valarray<bool> condition(point != point || point < lower_bounds || point > upper_bounds);

//     if(condition.sum() != 0) {
//         cout << "invalid point: " << endl;
//         for(int i=0; i<point.size(); ++i)
//             cout << point[i] << " ";
//         cout << endl;
//     }


	return condition.sum() == 0;
}

std::vector<double> JiaoPoll::initialDistribution() {
	double p = 5; //magic number, any prime number
	double q = pow(p,1./ (probDim + 1));

	valarray<double> d = upper_bounds - lower_bounds;
	vector<double> point(probDim);
	for(int i=0; i<probDim; ++i) {
		point[i]  = pow(q,i+1);
		point[i] *= pointsOut+1.;
		point[i] -= floor(point[i]);
		point[i] *= d[i];
		point[i] += lower_bounds[i];
	}

	++pointsOut;

	return point;
}

vector<double> JiaoPoll::randomPoint() const {

	valarray<double> point(probDim);

	generate_n(&point[0],point.size(),rand);

	valarray<double> span = upper_bounds - lower_bounds;
	point = point * (span / static_cast<double>(RAND_MAX)) + lower_bounds;


	return vector<double> (&point[0],&point[point.size()]);
}

static valarray<double> computeCentroid(const set<JiaoPoll::PopulationType::const_iterator>& idxFamily,
										const std::valarray<double>& weights) {

	set<JiaoPoll::PopulationType::const_iterator>::const_iterator itIdxFamily=idxFamily.begin();

	std::valarray<double> centroid((*itIdxFamily)->point().size());

	for(int k=0; itIdxFamily != idxFamily.end(); ++itIdxFamily, ++k) {
		for(int i=0; i< (*itIdxFamily)->point().size(); ++i) {
// 			cout << i << " point: " << ( ( *itIdxFamily )->point() )[i] << " weight: " << weights[k] << endl;
			centroid[i] += ((*itIdxFamily)->point()) [i] * weights[k] ;
		}
	}

// 	cout << "centroid: ";
// 	for(int i=0; i<centroid.size(); ++i)
// 		cout << " " << centroid[i];
// 	cout << endl;


	return centroid;
}

static double valueOfPair(const JiaoPoll::PopulationType::const_iterator& cit) {
	return cit->value();
}

valarray<double> JiaoPoll::computeWeights(const set<PopulationType::const_iterator>& idxFamily) {
	//compute phi
	double phi = probDim*delta*delta/deltaInit;

// 	cout << "phi " << phi << " delta " << delta << " deltaInit " << deltaInit << endl;

	//compute eta

	std::valarray<double> values(idxFamily.size());
	transform(idxFamily.begin(), idxFamily.end(),&values[0], valueOfPair);

// 	cout << "-- values " << endl;
// 	for(int i=0; i<values.size(); ++i)
// 		cout << values[i] << " ";
// 	cout << endl;

	std::valarray<double> eta(values.size());

// 	cout << "-- best " << endl;
// 	for(int i=0; i<population[0].point().size(); ++i)
// 		cout << population[0].point()[i] << " ";
// 	cout << endl;
// 	cout << "value: " << population[0].value() << endl;

	eta = 1. / (values - population[0].value() + phi);

// 	cout << "-- eta " << endl;
// 	for(int i=0; i<eta.size(); ++i)
// 		cout << eta[i] << " ";
// 	cout << endl;

	// compute weights
	return std::valarray<double> (eta/eta.sum());
}

std::valarray<double> JiaoPoll::controlledRandomPoint() {


	// create family index set
	set<PopulationType::const_iterator>  idxFamily = createFamilySet();

// 	cout << "-- family" << endl;
// 	for (set<PopulationType::const_iterator>::iterator it = idxFamily.begin(); it != idxFamily.end(); ++it) {
// 		const ValarrayValuePair& p = **it;
// 		for(int i=0; i<p.point().size(); ++i)
// 			cout << p.point()[i] << " ";
// 		cout << endl;
// 	}


	//take one point out
	PopulationType::const_iterator aPoint = *idxFamily.begin();
	idxFamily.erase(idxFamily.begin());


	std::valarray<double> weights = computeWeights(idxFamily);


	//TODO this is duplicated, already in computeWeights
	std::valarray<double> values(idxFamily.size());
	transform(idxFamily.begin(), idxFamily.end(),&values[0], valueOfPair);
	double phi = probDim*delta*delta/deltaInit;

//     cout << "-- weights " << endl;
//     for(int i=0; i<weights.size(); ++i)
//         cout << weights[i] << " ";
//     cout << endl;

	// compute centroid
	valarray<double> centroid(computeCentroid(idxFamily,weights));
	double f_w = (values * weights).sum();   //dot product

//     cout << "-- centroid " << endl;
//     for(int i=0; i<centroid.size(); ++i)
//         cout << centroid[i] << " ";
//     cout << endl;
//
//     cout << "-- new point" << endl;
//     cout << "f_w: " << f_w << endl;


	valarray<double> newPoint(probDim);

	if(f_w <= aPoint->value() || tooManyAttempts) {
		double alpha = 1 - (aPoint->value() - f_w) / (delta + phi);

//         cout << "alpha1: " << alpha << endl;

		newPoint = centroid - alpha * (aPoint->point() - centroid);
	} else {
		double alpha = 1 - (f_w - aPoint->value()) / (delta+phi);

//         cout << "alpha2: " << alpha << endl;

		newPoint = aPoint->point() - alpha * (centroid - aPoint->point());
	}

//     	for(int i=0; i<newPoint.size(); ++i)
// 		cout << newPoint[i] << " ";
// 	cout << endl;

	return newPoint;
}



std::set<JiaoPoll::PopulationType::const_iterator>
JiaoPoll::createFamilySet() {

	vector<int> indexVector;
	indexVector.reserve(population.size());
	for(int i=0, size= population.size(); i< size; ++i)
		indexVector.push_back(i);


	std::set<JiaoPoll::PopulationType::const_iterator> idxFamily;



	int size = std::min(population.size(), static_cast<size_t>(probDim + 1));

	while(idxFamily.size() < size) {
		double coeff= static_cast<double>(indexVector.size()) /RAND_MAX;

		int valIdx= static_cast<int>(rand() *coeff);

		if(valIdx== indexVector.size()) valIdx--;

		JiaoPoll::PopulationType::const_iterator chosen = population.begin();
		advance(chosen, indexVector[valIdx]);

		idxFamily.insert(chosen);	//set avoids repetitions

		vector<int>::iterator deleteIt = indexVector.begin();
		advance(deleteIt,valIdx);
		indexVector.erase(deleteIt);
	}

	return idxFamily;
}

void JiaoPoll::doFunctionComputed(const std::vector<double>&pointV , double value) {
	valarray<double> point(&pointV[0],pointV.size());

	ValarrayValuePair point_pair(make_pair(point,value));

	if(population.size() < par.populSize || value < worstValue)
		keepPoint(point_pair);
}


static bool swapMin(const JiaoPoll::PopulationType::iterator& from,
					const JiaoPoll::PopulationType::iterator to) {
	if(from < to) {
		JiaoPoll::PopulationType::iterator minIt = min_element(from,to);

		if(minIt != from) {
			ValarrayValuePair tmp = *minIt;
			*minIt = *from;
			*from = tmp;
			return true;
		}
	}

	return false;
}

void JiaoPoll::keepPoint(const ValarrayValuePair& point) {

	//if we are still filling the population just add the point
	if(population.size() < par.populSize) {
		population.push_back(point);

		PopulationType::const_iterator maxIt = max_element(population.begin(),population.end());
		PopulationType::const_iterator minIt = min_element(population.begin(),population.end());

		deltaInit = maxIt->value() - minIt->value();
	} else {
		//otherwise substitute the worst
		PopulationType::iterator maxIt = max_element(population.begin(),population.end());
		*maxIt = point;
	}

	//keep the three best values at the beginning
	if(population.size() > 3) {
		best3Changed = swapMin(population.begin(),population.end());
		best3Changed |= swapMin(population.begin() +1,population.end());
		best3Changed |= swapMin(population.begin() +2,population.end());
	}

	PopulationType::const_iterator maxIt = max_element(population.begin(),population.end());
	worstValue = maxIt->value();


	delta = maxIt->value() - population[0].value();

}



bool JiaoPoll::hasConverged() const {

	if(population.size() < par.populSize)
		return false;
	
	return delta <= par.minDelta;
}

double JiaoPoll::getBestValue() const {
	return population[0].value();
}

std::vector<double> JiaoPoll::getBestPoint() const {
	const valarray<double>& min = population[0].point();
	return vector<double> (&min[0],&min[min.size()]);
}

void JiaoPoll::saveTo(std::ostream& os) {

	for(int i=0, size = population.size(); i<size; ++i) {
		os << population[i].value() << " ";
		ostream_iterator<double> osIt(os, " ");

		copy(& (population[i].point() [0]),& (population[i].point() [probDim]),osIt);
		os << endl;
	}
}

void JiaoPoll::readFrom(std::istream& is) {

	string line;
	while(!is.eof()) {
		getline(is,line);
		if(line == "")
			break;

		stringstream ls(line);
		double value;
		ls >> value;

		istream_iterator<double> lsIt(ls), eof;
		vector<double> point;
		copy(lsIt,eof,back_inserter(point));
		doFunctionComputed(point,value);
	}

// 	cout << "population size: " << population.size() << endl;

	pointsOut = std::min(population.size(),static_cast<size_t>(par.populSize));
}

}


