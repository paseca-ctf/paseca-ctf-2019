r = open('r', 'rb').read()
g = open('g', 'rb').read()
b = open('b', 'rb').read()

o = open('out', 'wb')

for i in range(len(r)):
    if i % 3 == 0:
        o.write(bytes([r[i]]))
    if i % 3 == 1:
        o.write(bytes([g[i]]))
    if i % 3 == 2:
        o.write(bytes([b[i]]))

o.close()
