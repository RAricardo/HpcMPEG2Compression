import sys
from Lector import Lector
from Compresor import Compresor

def main():
    lector = Lector(sys.argv[1],sys.argv[2])
    lector.leer()
main()