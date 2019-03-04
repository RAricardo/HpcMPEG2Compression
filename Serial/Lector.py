from MacroBloque import MacroBloque
from PIL import Image

class Lector:
    def __init__(self, frame1, frame2):
        self.frame1 = frame1
        self.frame2 = frame2
    
    def leer(self):
        Pim1 = Image.open(self.frame1)
        Pim2 = Image.open(self.frame2)

        #Pim1 = im1.quantize()
        #Pim2 = im2.quantize()

        matrizPixeles1 = []
        for x in range(0,Pim1.width):
            matrizPixeles1.append([])
            for y in range(0,Pim1.height):
                matrizPixeles1[x].append(Pim1.getpixel((x,y)))

        #print(matrizPixeles1)
        matrizPixeles2 = []
        for x in range(0,Pim2.width):
            matrizPixeles2.append([])
            for y in range(0,Pim2.height):
                matrizPixeles2[x].append(Pim2.getpixel((x,y)))


        w = Pim1.width-15
        h = Pim1.height-15
        matrizMB1 = [[0 for x in range(w)] for y in range(h)]
        for x in range (0, len(matrizMB1)):
            for y in range (0, len(matrizMB1[x])):
                pixelesMB = []
                for i in range (x,16):
                    for j in range (y,16):
                        pixelesMB.append(matrizPixeles1[i][j])
                MB = MacroBloque(pixelesMB)
                matrizMB1[x][y] = MB

