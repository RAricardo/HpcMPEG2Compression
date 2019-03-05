import sys
from Lector import Lector
from Compresor import Compresor

def main():
    lector = Lector(sys.argv[1],sys.argv[2])
    matrices = lector.leer()
    compresor = Compresor(matrices[0], matrices[1])
    compresor.compresionMPEG2()
main()