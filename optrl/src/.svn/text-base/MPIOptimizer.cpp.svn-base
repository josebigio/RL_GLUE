#include <pargo/MPIOptimizer.h>


#include <pargo/Problem.h>
#include <pargo/Poll.h>

#include <mpi.h>

#include <map>
// #include <iostream>

namespace pargo {
	
	
	enum mpi_message_type {
		mpi_point_request = 1,
		mpi_value_request = 2,
		mpi_terminate_request = 3
	};
	
	unsigned long run_mpi_master(Poll *poll,unsigned long maxEvaluations) {
		
		unsigned long evaluationsLaunched = 0;
		
		int activeSlaves;
		MPI_Comm_size(MPI_COMM_WORLD,&activeSlaves);
		activeSlaves--; //substract master
		
		MPI_Request reqs[2] = {MPI_REQUEST_NULL, MPI_REQUEST_NULL};
		MPI_Request &pointRequest = reqs[0];
		MPI_Request &valueRequest = reqs[1];
		MPI_Status status;
		
		std::map<int, std::vector<double> > pointsOut;
		
		do {
			
			char buff;
			if(pointRequest == MPI_REQUEST_NULL)
				MPI_Irecv(&buff,1,MPI_CHAR, MPI_ANY_SOURCE,mpi_point_request,MPI_COMM_WORLD,&pointRequest);
			
			double value;
			if(valueRequest == MPI_REQUEST_NULL)
				MPI_Irecv(&value,1,MPI_DOUBLE, MPI_ANY_SOURCE, mpi_value_request, MPI_COMM_WORLD, &valueRequest);
			
			
			int index;
			MPI_Waitany(2,reqs,&index,&status);
			
			if(index == 0) {
				//point requests
				if(evaluationsLaunched < maxEvaluations && !poll->hasConverged()) {
					//create a new request
					std::vector<double> point = poll->nextPoint();
					pointsOut[status.MPI_SOURCE] = point;
					MPI_Send(&point[0],point.size(),MPI_DOUBLE,status.MPI_SOURCE,mpi_point_request,MPI_COMM_WORLD);
					++evaluationsLaunched;
				}
				else {
					//ask to terminate
					MPI_Send(&buff,1,MPI_CHAR,status.MPI_SOURCE,mpi_terminate_request,MPI_COMM_WORLD);
					pointsOut.erase(status.MPI_SOURCE);
					--activeSlaves;
				}
			}
			else {
				//value request
				poll->functionComputed(pointsOut[status.MPI_SOURCE],value);
				
			}
			
			
		} while(activeSlaves > 0);
		
		return evaluationsLaunched;
	}
	
	
	void run_mpi_slave(const Problem *problem) {
		
		bool exit = false;
		std::vector<double> point(problem->getn(),0);
		do {
			
			//request a new point
			char a = 'a'; //any character, the message is actually in the tag
			MPI_Send(&a,1,MPI_CHAR,0,mpi_point_request,MPI_COMM_WORLD);
			
			//receive point
			MPI_Status status;
			MPI_Recv(&point[0],point.size(),MPI_DOUBLE,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
			
			//check for termination request
			if(status.MPI_TAG == mpi_terminate_request)
				exit = true;
			else {
				
				//compute the function and send the value back to the master
				double value = problem->computef(point);
				MPI_Send(&value,1,MPI_DOUBLE,0,mpi_value_request,MPI_COMM_WORLD);
			}
			
		} while(!exit);
		
	}
	
	
}
