#include <pargo/approx/PolynomialFA.h>

// #include <iostream>

namespace pargo {

using namespace std;


unsigned int PolynomialFA::getNumBasisFunctions() const {

return computeFeatures(vector<double>(nvars)).size(); //maybe I'll do better one day
};

static void increment_indices(vector<int>& indices);

vector<double> PolynomialFA::computeFeatures ( const std::vector<double>& observations ) const{

	vector<double> features;

	features.push_back(1); //zero degree
	
	for(int d=1; d<= degree; ++d) {
		vector<int> indices(d);

// 		cout << "summing degree " << d << endl;

		while(indices[0] < nvars ) {

			double product = 1;
			for(int t=0; t<d; ++t) {
// 				cout << indices[t] << " ";
				product *= observations[indices[t]];
			}
// 			cout << endl;
				

			features.push_back(product);

			increment_indices(indices,indices.size()-1);

		}
		
	}

// 	cout << "size " << features.size() << endl;

	return features;
}

int PolynomialFA::increment_indices ( std::vector< int >& indices, int pos ) const {
	if(pos == 0)
		return ++indices[pos];
	
	if(indices[pos] + 1 == nvars)
		indices[pos] = increment_indices(indices,pos-1);
	else
		++indices[pos];
	
	return indices[pos];
}



}