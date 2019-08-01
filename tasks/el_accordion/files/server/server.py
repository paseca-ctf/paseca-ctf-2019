from binascii import hexlify, unhexlify
from random import randint as r
from sympy import nextprime as prime
from gmpy2 import powmod, invert

flag = 'paseca{f4m1l14r_s0ng}'

def s2i(s):
    return int(hexlify(bytes(s.encode('ascii'))), 16)
def i2s(i):
    return unhexlify(hex(i)[2:]).decode('ascii')

def gen_keys():
    p = prime(r(2 ** 128, 2 ** 256))
    g = r(1,p)

    x = r(2, p-1)
    k = r(2, p-2)
    
    y = powmod(g, x, p)
    return p, g, y, x, k

def encrypt(m, p, g, y, k):
    c1 = powmod(g, k, p)
    c2 = (powmod(y, k, p) * m) % p
    return int(c1), int(c2)
#TODO decrypt function


print('Welcome to El Accordion crypto service!')

p, g, y, x, k = gen_keys()
enc_flag = encrypt(s2i(flag), p, g, y, k)

print(f'Our public key: p = {p}, g = {g}, y = {y}')
while True:
    choice = input('[1] - Get encrypted flag\n[2] - Encrypt your message\n[3] - Decrypt your message\n[4] - Exit\n')
    if choice == '1':
        print(f'Encrypted flag: {enc_flag}')
    if choice == '2':
        m = input('Your message: ')
        if m:
            e = encrypt(s2i(m), p, g, y, k)
            print(f'You encrypted message: {e}')
        else:
            print('Empy message!')
    if choice == '3':
        print('TODO')
    if choice == '4':
        exit(0)
