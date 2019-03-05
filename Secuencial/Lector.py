from MacroBloque import MacroBloque
from PIL import Image

class Lector:
    def __init__(self, frame1, frame2):
        self.frame1 = frame1
        self.frame2 = frame2

    def llenarMatrizPixel(self, im):
        matrizPixeles = []
        for x in range(0,im.width):
            matrizPixeles.append([])
            for y in range(0,im.height):
                matrizPixeles[x].append(im.getpixel((x,y)))
        return matrizPixeles

    def crearMatrizMB(self, im, pixelMatrix):
        w = im.width-15
        h = im.height-15

        matrizMB = [[0 for x in range(w)] for y in range(h)]
        for x in range (0, len(matrizMB)):
            for y in range (0, len(matrizMB[x])):
                pixelesMB = []
                for i in range (x,16):
                    for j in range (y,16):
                        pixelesMB.append(pixelMatrix[i][j])
                MB = MacroBloque(pixelesMB)
                matrizMB[x][y] = MB
        return matrizMB

    def leer(self):
        im1 = Image.open(self.frame1)
        im2 = Image.open(self.frame2)

        if (im1.mode == 'RGB' and im2.mode == 'RGB'):
            im1.quantize()
            im2.quantize()
        
        matrizPixel1 = self.llenarMatrizPixel(im1)
        matrizPixel2 = self.llenarMatrizPixel(im2)

        MBmatrix1 = self.crearMatrizMB(im1, matrizPixel1)
        MBmatrix2 = self.crearMatrizMB(im2, matrizPixel2)

        matrices = (MBmatrix1, MBmatrix2)
        return matrices
        
