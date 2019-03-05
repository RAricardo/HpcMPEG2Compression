from MacroBloque import MacroBloque
from PIL import Image

class Lector:

    #Constructor de la clase lector, recibe dos imagenes.
    def __init__(self, frame1, frame2):
        self.frame1 = frame1
        self.frame2 = frame2

    #Crea una matriz de pixeles ordenados en coordenadas x, y a partir de un arreglo de pixeles
    def llenarMatrizPixel(self, im):
        matrizPixeles = []
        for x in range(0,im.width):
            matrizPixeles.append([])
            for y in range(0,im.height):
                matrizPixeles[x].append(im.getpixel((x,y)))
        return matrizPixeles

    #Crea un arreglo de macrobloques para una imagen a partir de una matriz de pixeles de la imagen.
    def crearArregloMB(self, pixelMatrix, w, h):
        arrMB = []
        for x in range (0, w):
            for y in range (0, h):
                pixelesMB = []
                for i in range (x,16):
                    for j in range (y,16):
                        pixelesMB.append(pixelMatrix[i][j])
                MB = MacroBloque(pixelesMB, x, y)
                arrMB.append(MB)
        return arrMB

    #Lee y estructura la informacion de las imagenes en Macrobloques.
    def leer(self):
        im1 = Image.open(self.frame1)
        im2 = Image.open(self.frame2)
        w = im1.width-15
        h = im2.height-15

        if (im1.mode == 'RGB' and im2.mode == 'RGB'):
            im1.quantize()
            im2.quantize()
        
        matrizPixel1 = self.llenarMatrizPixel(im1)
        matrizPixel2 = self.llenarMatrizPixel(im2)

        ArrMB1 = self.crearArregloMB(matrizPixel1, w, h)
        ArrMB2 = self.crearArregloMB(matrizPixel2, w, h)

        datos = (ArrMB1, ArrMB2, w, h)
        return datos
        
