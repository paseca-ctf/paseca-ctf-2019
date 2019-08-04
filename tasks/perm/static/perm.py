from random import shuffle as shake
from base64 import b64encode as bees_container

flag = 'b' + 'z'*47

flag_len = 12 * 6

secret_bzzz = -1337#bzz?

beehives = [flag[i:i+6][::-1] for i in range(0, flag_len, 6)]
paseca = [beehives[i:i+3] for i in range(0, len(beehives), 3)]

for i in range(len(paseca)):
    shake(paseca[i])
    for j in range(len(paseca[i])):
        paseca[i][j] = paseca[i][j][len(paseca[i][j])//2:] + paseca[i][j][:len(paseca[i][j])//2]

for i in range(0, len(paseca), 2):
    for j in range(len(paseca[i])):
        paseca[i][j] = [ord(paseca[i][j][k]) ^ ord(paseca[i+1][j][k]) for k in range(len(paseca[i][j]))]
        paseca[i+1][j] = [(ord(paseca[i+1][j][k])+secret_bzzz) ^ paseca[i][j][k] for k in range(len(paseca[i][j]))]

bad_paseca = paseca
bad_beehives = []
for i in bad_paseca:
    for j in i:
        bad_beehives.append(j)
bad_bees = b''
for bad_beehive in bad_beehives:
    for bad_bee in bad_beehive:
        bad_bees += bytes([bad_bee])
container_with_bad_bees = bees_container(bad_bees).decode('ascii')
bad_field = open('bad_field.txt', 'w')
bad_field.write(container_with_bad_bees)
bad_field.close()
