#include <iostream>
#include <vector>
#include "lector.cpp"
#include "macrobloque.cpp"
#include "compresor.cpp"
#include <mpi.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    if (world_rank == 0)
    {
        lector l = lector(argv[1], argv[2]);
        vector<vector<macrobloque>> datos = l.leer();
        compresor c = compresor(datos[0], datos[1]);
        time_t start = time(0);
    }
    else
    {
        c.compresionMPEG2();
        time_t stop = time(0);
        double time = (double)difftime(stop, start) * 1000.0;
        cout << time << endl;
        return 0;
    }
}
