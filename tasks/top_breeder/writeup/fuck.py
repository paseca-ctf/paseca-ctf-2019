from PIL import Image
import numpy as np

img = Image.open('out.png')
img = img.convert('RGB')
img = [[img.getpixel((i, j)) for i in range(img.size[0])] for j in range(img.size[1])]

def createImage(name, pixels):
    array = np.array(pixels, dtype=np.uint8)
    image = Image.fromarray(array)
    image.save('{}.png'.format(name))

def horizontalSlice(img):
    top = []
    bottom = []

    h = len(img)
    w = len(img[0])

    for j in range(h):
        if j < h // 2:
            top.append([])
            for i in range(w):
                top[-1].append(img[j][i])
        else:
            bottom.append([])
            for i in range(w):
                bottom[-1].append(img[j][i])

    return top, bottom

def verticalSlice(img):
    left = []
    right = []

    h = len(img)
    w = len(img[0])

    for j in range(h):
        left.append([])
        right.append([])
        for i in range(w):
            if i < w // 2:
                left[-1].append(img[j][i])
            else:
                right[-1].append(img[j][i])

    return left, right

def sliceImage(img):
    l, r = verticalSlice(img)
    lt, lb = horizontalSlice(l)
    rt, rb = horizontalSlice(r)

    new_img = []
    for i in range(len(img)):
        new_img.append([])
        for j in range(len(img[0])):
            if i % 2 == 0:
                if j % 2 == 0:
                    new_img[i].append(lt[i//2][j//2])
                else:
                    new_img[i].append(rt[i//2][j//2])
            else:
                if j % 2 == 0:
                    new_img[i].append(lb[i//2][j//2])
                else:
                    new_img[i].append(rb[i//2][j//2])

    return new_img

for i in range(3):
    img = sliceImage(img)
createImage('flag', img)