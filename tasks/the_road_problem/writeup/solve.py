from PIL import Image
import numpy as np

inf = 1e9

def createImage(name, pixels):
    array = np.array(pixels, dtype=np.uint8)
    image = Image.fromarray(array)
    image.save('{}.png'.format(name))

def sgn(x):
    if x < 0: return -1
    else: return 1

def findPath(w):
    d = [inf for _ in range(5776)]
    d[0] = 0
    u = [0 for _ in range(5776)]
    tmp = [-1 for _ in range(5776)]

    v = 0
    while u[v] == 0:
        u[v] = 1
        for e in w[v]:
            if d[e[0]] > d[v] + e[1]:
                d[e[0]] = d[v] + e[1]
                tmp[v] = e[0]
        v = 0
        m = inf
        for i in range(5776):
            if u[i] == 0 and d[i] < m:
                v = i
                m = d[i]
    
    path = [0]
    v = 0
    while tmp[v] != -1:
        path.append(tmp[v])
        v = tmp[v]

    return d, path

w = [[] for _ in range(5776)]
f = open('input.txt').read().split('\n')[:-1]
v = 0
for i in range(len(f)):
    e = f[i].split()
    if len(e) == 1:
        v = int(e[0])
    else:
        u, W = int(e[0]), int(e[1])
        w[v].append([u, W])

d, path = findPath(w)
weights = []
for i in range(1, len(path)):
    weights.append(d[path[i]] - d[path[i-1]])

def line(x1, y1, c):
    if x == x1:
        d = sgn(y1 - y)
        for Y in range(y, y1, d):
            for m in range(10):
                img[10*Y+m*d][10*x] = c
    else:
        d = sgn(x1 - x)
        for X in range(x, x1, d):
            for m in range(10):
                img[10*y][10*X+m*d] = c

img = Image.open('map.png')
img.convert('RGB')
img = [[img.getpixel((j, i)) for j in range(751)] for i in range(751)]
x, y = 0, 0
for e in path:
    line(e % 76, e // 76, (232, 199, 60))
    x = e % 76
    y = e // 76

x, y = 0, 0
for e in [(weights[i], weights[i+1]) for i in range(0, len(weights), 2)]:
    line(e[0], e[1], (170, 114, 45))
    x = e[0]
    y = e[1]

createImage('flag', img)
