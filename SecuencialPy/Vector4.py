class Vector4:
    def __init__(self,i, j, x, y):
        self.i = i
        self.j = j
        self.x = x
        self.y = y

    def imprimir(self):
        print("MB(" + str(self.i) + "," + str(self.j) + ")=(x"+ str(self.x) + ",y" + str(self.y)+") ")
