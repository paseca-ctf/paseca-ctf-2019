from sys import argv
import socket

ip = argv[1]
port = argv[2]

sock = socket.socket()
sock.connect((ip, int(port)))
print('#1 Yes')
print(sock.recv(200))
sock.send(b'2\n')
print(sock.recv(200))
sock.send(b'admina\n')
print(sock.recv(200))
sock.send(b'dmin\n')
print(sock.recv(200))
sock.send(b'1\n')
print(sock.recv(200))
sock.send(b'admina\n')
print(sock.recv(200))
sock.send(b'dmin\n')
print(sock.recv(200))
sock.send(b'1\n')
data = sock.recv(200)
sock.close()

print(data)
data = b'paseca{th15_h0n3y_t4st35_b4d_c4us3_1t_1s_s4lty_l0000l}' in  data
print(data)
if data:
    exit(0)
else:
    exit(1)
