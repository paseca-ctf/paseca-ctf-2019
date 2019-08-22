from random import shuffle


data = list([i for i in range(32)])
print(sum(data))
shuffle(data)

print(''.join([hex(i)[2:].zfill(2) for i in data]))
print(data)