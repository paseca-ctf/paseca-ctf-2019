data = [215, 229, 411, 114, 380, 812, 655, 34, 631, 80, 849, 274, 720, 561, 586, 584, 147, 721, 337, 140, 747, 289, 378, 378, 312, 375, 559, 389, 654, 510, 98, 687]
magic = 0x1337

g, m = 747, 907
dec = []
for i in data:
    for j in range(m):
        if (g ** j) % m == i:
            num = magic - j
            print('[+] {} = {} = {}'.format(i, j, num))
            magic -= num
            dec.append(num)

print(len(dec))
