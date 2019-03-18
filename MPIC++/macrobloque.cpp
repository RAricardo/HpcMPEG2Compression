#pragma once
#include <vector>
#include <iostream>
#include <omp.h>
using namespace std;

class macrobloque
{
public:
  int x, y;
  int arr [];
  macrobloque() {}
  macrobloque(vector<int> arr, int x, int y)
  {
    this->x = x;
    this->y = y;
    int newArr[225];
    copy(arr.begin(), arr.end(), newArr);
    this->arr = newArr;
  }

  int comparar(macrobloque MB)
  {
    int contadorCoincidencias = 0;
    for (int i = 0; i < 225; ++i){
        if (arr[i] != MB.arr[i]){
	      #pragma omp atomic
          ++contadorCoincidencias;
        }
      }
    return contadorCoincidencias;
  }
};
