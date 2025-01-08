import time
from PIL import Image
import numpy as np
from flask import Flask, request, send_file
import matplotlib.pyplot as plt

def readFile(input_string):
    rows = input_string.strip().split('\n')
    height = len(rows)
    width = len(rows[0].split(' ')) if height > 0 else 0
    array = np.zeros((height, width, 3), dtype=np.uint8)

    for i, row in enumerate(rows):
        pixels = row.split(' ')[0:-1]
        for j, pixel in enumerate(pixels):
            array[i, j] = [int(pixel[1:3], 16), int(pixel[3:5], 16), int(pixel[5:7], 16)]
    
    image = Image.fromarray(array, 'RGB')
    return image
    
    
app = Flask(__name__)


@app.route("/update", methods=["POST"])
def receive():
    imageData = request.data.decode("utf-8")
    image = readFile(imageData)
    image.save("test.png")
    return "OK"
    
@app.route("/")
def home():
    return send_file("test.png", mimetype='image/png')

if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0")