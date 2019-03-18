#pragma once
#include <iostream>
#include <vector>
#include "macrobloque.cpp"
#include "vector4.cpp"
#include <omp.h>
#include <mpi.h>
#include <cstddef>

using namespace std;

class compresor
{
  private:
    vector<macrobloque> MBArr1;
    vector<macrobloque> MBArr2;

  public:
    compresor() {}
    compresor(vector<macrobloque> MBArr1, vector<macrobloque> MBArr2)
    {
        this->MBArr1 = MBArr1;
        this->MBArr2 = MBArr2;
    }

    void compresionMPEG2()
    {
        MPI_Init(NULL, NULL);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        //Insertar codigo para transformar MBArr2 y MBArr1 en datos enviables //Paralerizar
        //Transformando MBarr2 en mb2
        MPI_Datatype MBTYPE;
        MPI_Datatype type[3] = {MPI_INT, MPI_INT, MPI_INT};
        int blocklen[3] = {1, 1, 225};
        MPI_Aint disp[3];
	disp[0] = (MPI_Aint)offsetof(class macrobloque, x);
	disp[1] = (MPI_Aint)offsetof(class macrobloque, y);
	disp[2] = (MPI_Aint)offsetof(class macrobloque, arr);
	//Se crea la estructura
        MPI_Type_create_struct(3, blocklen, disp, type, &MBTYPE);
        MPI_Type_commit(&MBTYPE);
        //Se crea cada arreglo de MBTYPE
        //mbarr2
	int size2=MBArr2.size();
	int size1=MBArr1.size();
	macrobloque mb2 [MBArr2.size()];
	macrobloque mb1 [MBArr1.size()];
        int tamEnviar = size1 / world_size;

        if (world_rank == 0){
            mb2[MBArr2.size()];
            copy(MBArr2.begin(), MBArr2.end(), mb2);

            //mbarr1
            mb1[MBArr1.size()];
            copy(MBArr1.begin(), MBArr1.end(), mb1);
        }

	macrobloque mb1rec[tamEnviar];
	MPI_Barrier(MPI_COMM_WORLD);
        MPI_Bcast(mb2, size2, MBTYPE, 0, MPI_COMM_WORLD);
        MPI_Scatter(mb1, tamEnviar, MBTYPE, mb1rec, tamEnviar, MBTYPE, 0, MPI_COMM_WORLD);
#pragma omp parallel for schedule(dynamic, 8)
        for (int i = 0; i < tamEnviar; ++i)
        {
            int valMin = 256;
            vector4 vector = vector4(0,0,0,0);
            bool compZero = false;
            int comparacion;
            for (int j = 0; j < size2; ++j)
            {
                if (compZero)
                {
                    compZero = true;
                }
                else
                {
                    comparacion = mb1rec[i].comparar(mb2[j]);
                    if (comparacion == 0)
                    {
                        vector = vector4(mb1rec[i].x, mb1rec[i].y, mb2[j].x, mb2[j].y);
                        compZero = true;
                    }
                    else if (comparacion <= valMin)
                    {
                        valMin = comparacion;
                        vector = vector4(mb1rec[i].x, mb1rec[i].y, mb2[j].x, mb2[j].y);
                    }
                }
            }
            vector.imprimir();
	    }
        MPI_Finalize();
    }
};
