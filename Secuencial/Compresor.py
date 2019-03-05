from MacroBloque import MacroBloque
from Vector4 import Vector4

class Compresor:

    #Recibe dos arreglos de macrobloques para realizar Compresion MPEG2
    def __init__(self, MBArr1, MBArr2, w, h):
        self.MBArr1 = MBArr1
        self.MBArr2 = MBArr2
        self.matrizVectores = [[0 for x in range(w)] for y in range(h)]

    #Aplica el arreglo de compresión a los grupos de macrobloques
    def compresionMPEG2(self):
        for i in range(len(self.MBArr1)):
            valMin = 256
            vector = None
            for j in range(len(self.MBArr2)):
                comparacion = self.MBArr1[i].comparar(self.MBArr2[j])
                if (comparacion == 0):
                    vector = Vector4(self.MBArr1[i].x, self.MBArr1[i].y, self.MBArr2[j].x, self.MBArr2[j].y)
                elif (comparacion < min):
                    min = comparacion
                    vector = Vector4(self.MBArr1[i].x, self.MBArr1[i].y, self.MBArr2[j].x, self.MBArr2[j].y)
            self.matrizVectores[self.MBArr1[i].x][self.MBArr1[i].y] = vector
    
    #Imprime los resultados en forma de matriz de vectores de movimiento
    def imprimirResultados(self):
        for i in range(len(self.matrizVectores)):
            print('\n')
            for j in range(len(self.matrizVectores[0])):
                self.matrizVectores[i][j].imprimir()
