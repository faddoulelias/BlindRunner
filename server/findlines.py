import time
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

def showImage(dataArray):
    plt.imshow(dataArray, cmap= "seismic")
    plt.show()
    
def readFile(filename):
    img = Image.open(filename)
    img = img.convert("L")
    img = img.resize((96, 96))
    data = np.asarray(img)
    data = np.where(data > 128, 1, 0)
    return data
    
class Line():
    def __init__(self, x, y, length, angle): # angle is in degrees
        self.x = x
        self.y = y
        self.length = length
        self.angle = np.radians(angle)
        
    def setAngle(self, angle):
        self.angle = np.radians(angle)
        
    def overlappingPercentage(self, data):
        x = self.x
        y = self.y
        length = self.length
        angle = self.angle
        count = 0
        for i in range(length):
            x = self.x + i * np.cos(angle)
            y = self.y + i * np.sin(angle)
            if x < 0 or x >= data.shape[0] or y < 0 or y >= data.shape[1]:
                break
            if data[int(x), int(y)] == 1:
                count += 1
        return count / length
    
    def draw(self, data):
        x = self.x
        y = self.y
        length = self.length
        angle = self.angle
        for i in range(length):
            x = self.x + i * np.cos(angle)
            y = self.y + i * np.sin(angle)
            if x < 0 or x >= data.shape[0] or y < 0 or y >= data.shape[1]:
                break
            data[int(x), int(y)] = 2
            
        return data

data = readFile("test2.png")



def findBestLine(data, x, y):
    bestLine = None
    bestPercentage = 0
    for angle in range(180):
        line = Line(x, y, 30, angle)
        percentage = line.overlappingPercentage(data)
        if percentage > bestPercentage:
            bestLine = line
            bestPercentage = percentage
    
    return (bestLine, bestPercentage)


def findLines(data):
    lines = {}
    for x in range(0, data.shape[0], 30):
        for y in range(data.shape[1]):
            print(x, y)
            if data[x, y] == 1:
                line, percentage = findBestLine(data, x, y)
                if line and percentage > 0.9:
                    lines[(x, y)] = (line, percentage)
                    
    return lines
    

lines = findLines(data)
for (x, y), (line, percentage) in lines.items():
    data = line.draw(data)

showImage(data)