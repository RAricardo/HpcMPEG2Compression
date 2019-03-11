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
    def crearArregloMB16x16(self, pixelMatrix, w, h):
        arrMB = []
        for x in range (0,w, 16):
            for y in range (0, h, 16):
                pixelesMB = []
                for i in range (x,x+15):
                    for j in range (y,y+15):
                        pixelesMB.append(pixelMatrix[i][j])
                MB = MacroBloque(pixelesMB, x, y)
                arrMB.append(MB) 
        return arrMB

    def crearArregloMBpxp(self, pixelMatrix, w, h):
        arrMB = []
        for x in range (0,w-15):
            for y in range (0, h-15):
                pixelesMB = []
                for i in range (x,x+15):
                    for j in range (y,y+15):
                        pixelesMB.append(pixelMatrix[i][j])
                MB = MacroBloque(pixelesMB, x, y)
                arrMB.append(MB) 
        return arrMB

    #Lee y estructura la informacion de las imagenes en Macrobloques.
    def leer(self):
        im1 = Image.open(self.frame1)
        im2 = Image.open(self.frame2)

        w = im1.width
        h = im1.height

        if (im1.mode == 'RGB' and im2.mode == 'RGB'):
            im1.quantize()
            im2.quantize()
        
        matrizPixel1 = self.llenarMatrizPixel(im1)
        matrizPixel2 = self.llenarMatrizPixel(im2)

        ArrMB1 = self.crearArregloMB16x16(matrizPixel1, w, h)
        print(len(ArrMB1))
        ArrMB2 = self.crearArregloMBpxp(matrizPixel2, w, h)
        print(len(ArrMB2))
        datos = (ArrMB1, ArrMB2, w, h)
        return datos
        
