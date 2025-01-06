import time
from PIL import Image
import numpy as np
from flask import Flask, request, send_file

def readFile(dataString):
    w, h = 96, 96
    data = np.zeros((h, w, 3), dtype=np.uint8)
    data[0:256, 0:256] = [255, 0, 0]

    lines = dataString.split("\n")
    for i in range(len(lines)):
        pixels = list(map(int, lines[i].split()))
        for j in range(len(pixels)):
            data[i][j] = [pixels[j], pixels[j], pixels[j]]

    img = Image.fromarray(data, 'RGB')
    return img
    
    
app = Flask(__name__)

last_saved_time = 0

@app.route("/update", methods=["POST"])
def receive():
    file = open("test.txt", "w")
    file.write(request.data.decode("utf-8"))
    print(request.data.decode("utf-8"))
    file.close()
    return "success"

@app.route("/")
def home():
    return send_file("test.png", mimetype='image/png')

if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0")