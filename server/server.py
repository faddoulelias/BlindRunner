import time
from PIL import Image
import numpy as np
from flask import Flask, request, send_file

def readFile(dataString):
    # the dataString represents an image
    # each row is a row of the image
    # each row consists of n pixels separated by ";"
    # each pixel consists of 3 values separated by ","
    image = []
    rows = dataString.split("\n")[0:-1]
    for row in rows:
        pixels = row.split(";")[0:-1]
    image.append([list(map(int, pixel.split(","))) for pixel in pixels])
    
    image = np.array(image, dtype=np.uint8)
    return Image.fromarray(image)
    
    
app = Flask(__name__)

last_saved_time = 0

@app.route("/update", methods=["POST"])
def receive():
    imageData = request.data.decode("utf-8")
    image = readFile(imageData)
    image.save("test.png")
    
    return "success"

@app.route("/")
def home():
    return send_file("test.png", mimetype='image/png')

if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0")