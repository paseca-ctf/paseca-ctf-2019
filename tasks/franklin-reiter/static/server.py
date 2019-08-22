from gmpy2 import powmod, invert
from Crypto.Util.number import getPrime as prime

flag = <redacted>

p = prime(512)
q = prime(512)

n = p*q
t = (p-1)*(q-1)

e = 0b10001
d = invert(e,t)

public = (e,n)
private = (d,n)

enc_flag = powmod(flag, e, n)



def pad(m):
    global p
    if p.bit_length() + m.bit_length() < n.bit_length():
        return True, (p << m.bit_length()) + m
    else:
        return False, 'Error: message too big'

print('bzzz')
print('public key: ', public)
print('encrypted flag: ', enc_flag)
while True:
    choice = input('[E]ncrypt\n[D]ecrypt\n> ')
    if choice == 'E':
        try:
            m = int(input('m: '))
        except:
            print('Error: invalid message')
            exit()
        pad_res, m = pad(m)
        if pad_res:
            print('c:', powmod(m, e, n))
        else:
            print(m)
    elif choice == 'D':
        print('TODO')
        
