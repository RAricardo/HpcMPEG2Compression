from MacroBloque import MacroBloque
from Vector2 import Vector2

class Compresor:

    def __init__(self, matrizMB1, matrizMB2):
        w, h = matrizMB1.width, matrizMB1.height
        self.matrizVectores = [[0 for x in range(w)] for y in range(h)]

    #def compresionMPEG2(self):