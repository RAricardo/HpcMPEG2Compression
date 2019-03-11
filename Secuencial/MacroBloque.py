class MacroBloque:

    #Crea un macrobloque a partir de un arreglo de pixeles, y la posición de este macrobloque.
    def __init__(self, arr, x, y):
        self.arr = arr
        self.x = x
        self.y = y
    
    #Compara este macrobloque con otro macrobloque
    def comparar(self, MB):
        contadorCoincidencias = 0
        for i in range(len(MB.arr)):
            if(self.arr[i] != MB.arr[i]):
                contadorCoincidencias = contadorCoincidencias+1
        return contadorCoincidencias
