from base64 import b64decode as d
from string import printable
from itertools import permutations as perm

def check(s):
    global printable
    for i in s:
        if i not in printable:
            return False
    return True

bad_field = open('bad_field.txt', 'r').read()

enc = []
for i in d(bad_field):
    enc.append(i)

enc = [enc[i:i+6][::-1] for i in range(0, len(enc), 6)]
enc = [enc[i:i+3] for i in range(0, len(enc), 3)]
print(enc)
#sec_bz = 73
back_enc = []
for i in range(len(enc)):
    back_enc.append([])
    for j in range(len(enc[i])):
        back_enc[i].append([])
        back_enc[i][j] = enc[i][j].copy()

lever3 = False
for sec_bz in range(1000):
    if lever3:
        break
    lever2 = False
    lever = False
    enc = []
    for i in range(len(back_enc)):
        enc.append([])
        for j in range(len(back_enc[i])):
            enc[i].append([])
            enc[i][j] = back_enc[i][j].copy()
        
    for i in range(0, len(enc), 2):
        
        for j in range(len(enc[i])):
            e1 = enc[i][j]
            e2 = enc[i+1][j]

            e2 = [((e1[k] ^ e2[k])-sec_bz) for k in range(len(e1))]
            e1 = [e1[k] ^ e2[k] for k in range(len(e1))]

            
            enc[i][j] = ''.join(chr(k) for k in e1)
            enc[i+1][j] = ''.join(chr(k) for k in e2)
            #print((check(enc[i][j]) and check(enc[i+1][j]) and input(f'looks good?[y] "{enc[i][j]}, {enc[i+1][j]}"') == 'y'))
            if lever2 or (check(enc[i][j]) and check(enc[i+1][j]) and input(f'looks good?[y] "{enc[i][j]}, {enc[i+1][j]}"') == 'y'):
                lever2 = True
                lever3 = True
                continue
            else:
                lever = True
                break
        if lever:
            break


for i in range(len(enc)):
    for j in range(len(enc[i])):
        enc[i][j] = enc[i][j][3:] + enc[i][j][:3]

flag = ''
for i in range(len(enc)):
    lever = False
    while not lever:
        for j in perm(enc[i]):
            piece = ''.join(j)
            if input(f'nice?[y] "{piece}"') == 'y':
                flag += piece
                lever = True
                break
print(flag)

