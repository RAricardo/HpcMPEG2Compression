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
    vector<macrobloque>MBArr1;
    vector<macrobloque> MBArr2;

  public:
  compresor(){}
  compresor(vector<macrobloque>MBArr1, vector<macrobloque>MBArr2){
      this->MBArr1=MBArr1;
      this->MBArr2=MBArr2;
  }

  void compresionMPEG2(){

#pragma omp parallel for schedule(dynamic, 8)
    for(int i=0;i<MBArr1.size();++i){
        int valMin=256;
        vector4 vector;
        bool compZero = false;
	    int comparacion;	    
	    // #pragma omp parallel for schedule(guided)
            for(int j=0;j<MBArr2.size();++j){
                if (compZero) {
                    compZero = true;
                } else {
                     comparacion = MBArr1[i].comparar(MBArr2[j]);
                    if(comparacion==0){
		       vector=vector4(MBArr1[i].x, MBArr1[i].y, MBArr2[j].x, MBArr2[j].y);
                       compZero = true;
                    }
                    else if(comparacion<=valMin){
                        valMin=comparacion;
                        vector=vector4(MBArr1[i].x, MBArr1[i].y, MBArr2[j].x, MBArr2[j].y);
                    }
                }
            }
	    vector.imprimir();      
        }
    }
};
