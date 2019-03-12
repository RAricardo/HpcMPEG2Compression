#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "macrobloque.cpp"
#include <string>

using namespace std;

class lector
{
  private:
    char* frame1;
    char* frame2;
    int w;
    int h;

  public:
    lector(){

    }

    lector(char* frame1, char* frame2)
    {
        this->frame1 = frame1;
        this->frame2 = frame2;
    }

    vector<vector<string> > llenarMatrizPixeles(char *filename)
    {
        int c;
        FILE *f = fopen(filename, "rb");
        unsigned char info[54];
        fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

        int width = *(int *)&info[18];
        int height = *(int *)&info[22];

        this->w = width;
        this->h = height;

        int size = 3 * width * height;
        unsigned char *data = new unsigned char[size]; // allocate 3 bytes per pixel
        fread(data, sizeof(unsigned char), size, f);   // read the rest of the data at once
        fclose(f);

        vector<string> pixeles = vector<string>(width * height);

        for (c = 0; c < size; c += 3)
        {
            stringstream ss;
            ss << data[c];
            ss<< data[c + 1];
            ss<< data[c + 2];
            string p;
            ss >> p;
            pixeles.push_back(p);
        }

        vector<vector<string> > matrizPixeles = vector<vector<string> >(width);
        for (int i = 0; i < matrizPixeles.size(); ++i)
        {
            vector<string> columna = vector<string>(height);
            matrizPixeles.push_back(columna);
            for (int j = 0; j < matrizPixeles[i].size(); ++j)
            {
                matrizPixeles[i].push_back(pixeles.front());
                pixeles.erase(pixeles.begin());
            }
        }
        return matrizPixeles;
    }

    vector<macrobloque> crearArregloMB16x16(vector<vector<string> > pixelMatrix, int w, int h){
        vector<macrobloque> arrMB;
        for (int x = 0; x < w; x + 16){
            for (int y = 0; y < h; y + 16){
                vector<string> pixelesMB;
                for (int i = x; i < x + 15; ++i){
                    for (int j = y; j < j + 15; ++j){
                        pixelesMB.push_back(pixelMatrix[i][j]);
                    }
                }
                macrobloque MB = macrobloque(pixelesMB, x, y);
                arrMB.push_back(MB);
            }
        }
        return arrMB;
    }

    vector<macrobloque> crearArregloMBpxp(vector<vector<string> > pixelMatrix, int w, int h){
        vector<macrobloque> arrMB;
        for (int x = 0; x < w-15; ++x){
            for (int y = 0; y<h-15; ++y){
                vector<string> pixelesMB;
                for (int i = x; i < x + 15; ++i){
                    for (int j = y; j < j + 15; ++j){
                        pixelesMB.push_back(pixelMatrix[i][j]);
                    }
                }
                macrobloque MB = macrobloque(pixelesMB, x, y);
                arrMB.push_back(MB);
            }
        }
        return arrMB;
    }

    vector<vector<macrobloque> > leer(){
        vector<vector<string> > matrizPixel1 = llenarMatrizPixeles(this->frame1);
        vector<vector<string> > matrizPixel2 = llenarMatrizPixeles(this->frame2);

        vector<macrobloque> ArrMB1 = crearArregloMB16x16(matrizPixel1, w, h);
        vector<macrobloque> ArrMB2 = crearArregloMBpxp(matrizPixel2, w, h);

        vector<vector<macrobloque> > datos;

        datos.push_back(ArrMB1);
        datos.push_back(ArrMB2);

        return datos;
    }
};