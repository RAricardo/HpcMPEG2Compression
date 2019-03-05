import sys
from Lector import Lector
from Compresor import Compresor

#Metodo Main, lee dos imagenes y aplica el algoritmo de compresion MPEG2.
def main():
    lector = Lector(sys.argv[1],sys.argv[2])
    datos = lector.leer()
    compresor = Compresor(datos[0], datos[1], datos[2], datos[3])
    compresor.compresionMPEG2()
    compresor.imprimirResultados()
main()