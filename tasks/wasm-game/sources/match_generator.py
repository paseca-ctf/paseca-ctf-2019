key = [13, 4, 6, 28, 31, 29, 14, 24, 12, 15, 10, 23, 19, 26, 5, 8, 27, 25, 30, 22, 17, 3, 1, 0, 9, 2, 21, 11, 20, 18, 7, 16]
for i in sorted(list(enumerate(key)), key=lambda x: x[1]):
    print('x = {} y = {}'.format(i[0] % 8 + 1, i[0]//8 + 1))
print(''.join([hex(i)[2:].zfill(2) for i in key]))
g, m = 747, 907
magic = 0x1337
xor = 0x88
hive = []
hive_xor = []
for i in key:
    hive_xor.append(i ^ xor)

print(hive_xor)

for i in key:
    hive.append((g**(magic - i)) % m)
    magic -= i

print(hive)
