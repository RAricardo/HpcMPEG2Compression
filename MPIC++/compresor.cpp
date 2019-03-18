#pragma once
#include <iostream>
#include <vector>
#include "macrobloque.cpp"
#include "vector4.cpp"
#include <omp.h>
#include <mpi.h>

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
        //Se calculan los displacements de cada atributo
        int sampleArr[225] = {};
        macrobloque sampleMB = macrobloque(1, 1, sampleArr)
            MPI_Aint disp[3];

        disp[0] = &sampleMB.x - &sampleMB;
        disp[1] = &sampleMB.y - &sampleMB;
        disp[2] = &sampleMB.arr - &sampleMB;

        //Se crea la estructura
        MPI_Type_create_struct(3, blocklen, disp, type, &MBTYPE);
        MPI_Type_commit(&MBTYPE);

        //Se crea cada arreglo de MBTYPE y se calculan sus displacements
        //mbarr2
        if (world_rank = 0)
        {
            macrobloque mb2[MBarr2.size()];
            copy(mb2.begin(), mb2.end(), mb2);
            //mbarr1
            macrobloque mb1[MBarr1.size()];
            copy(mb1.begin(), mb1.end(), mb1);

            int size2 = MBArr2.size();
            int size1 = MBArr1.size();

            int esclavos = world_size - 1;
            int tamEnviar = size1 / esclavos;
        }

        MPI_Bcast(mb2, size2, MBTYPE, 0, MPI_COMM_WORLD);
        MPI_Scatter(mb1, tamEnviar, MBTYPE, mb1rec,
                    tamEnviar, MBTYPE, 0, MPI_COMM_WORLD);
#pragma omp parallel for schedule(dynamic, 8)
        for (int i = 0; i < tamEnviar; ++i)
        {
            int valMin = 256;
            vector4 vector;
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
