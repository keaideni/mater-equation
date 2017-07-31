#include "master.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "mpi.h"

using namespace std;


int main(int argc, char* argv[])
{
        
        MPI_Status status;

        int myid, numprocess;

        int groupn(180);
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &myid);
        MPI_Comm_size(MPI_COMM_WORLD, &numprocess);

        int everygroup(groupn/numprocess);

        if(myid==0)
        {
                ofstream outfile("result");
                std::vector<double> res(groupn);
                
                for(int i=0; i<everygroup; ++i)
                {
                        double delta(0.001*i+0.9);
                        master M(delta, delta-0.05, 0.05, 0.005, 0.005, 0.005);
                        res.at(i)=abs(M.phi1());
                        


                }

                

                for(int id=1; id<numprocess; ++id)
                {
                        //std::vector<double> res(everygroup);

                        
                        MPI_Recv(&res[everygroup*id], everygroup, MPI_DOUBLE, id, id, MPI_COMM_WORLD, &status);
                        
                }
                
                for(int i=0; i<groupn; ++i)
                {
                        outfile<<0.9+0.001*i<<"\t"<<res.at(i)<<endl;
                }

                
                outfile.close();
                

        }else
        {
                std::vector<double> res(everygroup);
                for(int i=0; i<everygroup; ++i)
                {
                        double delta(0.001*(everygroup*myid+i)+0.9);
                        master M(delta, delta-0.05, 0.05, 0.005, 0.005, 0.005);
                        res.at(i)=abs(M.phi1());

                }

                MPI_Send(&res[0], everygroup, MPI_DOUBLE, 0, myid, MPI_COMM_WORLD);

        }



        MPI_Finalize();
}