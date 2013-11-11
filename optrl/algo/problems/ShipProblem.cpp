#include "ShipProblem.h"
#include <iostream>

#include <mpi.h>

extern "C" { void warp_interface_(double [], const int &, double [], const int &, const int &, const int &, const int &); }

namespace pargo {

using namespace std;

int ShipProblem::getn() const {
	return 5;
}

double ShipProblem::computef ( const std::vector<double>& x ) const {
	double * f = new double[2];
	double * y = const_cast<double*>( &x[0] );
	int iresolution=2;	//low
	int imorph=1;	//1A
	int rank = MPI::COMM_WORLD.Get_rank();
	warp_interface_(y,5,f,2,imorph,iresolution,rank);

	double ret = f[1]/f[0];
	if(ret > 1000)
		ret = 1000;
	
	ret *= 1000;
	delete []f;
	return ret;
}

std::vector<BoundsPair> ShipProblem::getBounds() const {
  return vector<BoundsPair>(getn(),make_pair(0.,1.) );
}

}
