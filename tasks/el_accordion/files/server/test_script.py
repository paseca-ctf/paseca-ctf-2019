import socket
from sys import argv
from binascii import hexlify, unhexlify
from gmpy2 import powmod, invert

def s2i(s):
    return int(hexlify(bytes(s.encode('ascii'))), 16)
def i2s(i):
    return unhexlify(hex(i)[2:]).decode('ascii')


sock = socket.socket()
ip = argv[1]
port = int(argv[2])

sock.connect((ip, port))

n_p_k = sock.recv(2048).decode('ascii')
n_p_k = n_p_k.split(',')

p = int(n_p_k[0].split(' ')[-1])
g = int(n_p_k[1].split(' ')[-1])
y = int(n_p_k[2].split(' ')[3][:-4])

sock.send(b'1\n')

n_p_f = sock.recv(2048).decode('ascii')

cc = n_p_f[17:-92].split(', ')
f_c1 = int(cc[0])
f_c2 = int(cc[1])

plain = s2i('asd')
sock.send(b'2\n')
sock.recv(1024)
sock.send(b'asd\n')
n_p_p = sock.recv(2048).decode('ascii')

p_cc = n_p_p[24:-92].split(', ')
p_c1 = int(p_cc[0])
p_c2 = int(p_cc[1])

sock.send(b'4\n')

inv_p = invert(plain, p)
y_k = (p_c2*inv_p) % p
inv_y_k = invert(y_k, p)
flag = (inv_y_k * f_c2) % p
print(i2s(flag))
