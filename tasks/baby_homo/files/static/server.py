from Crypto.Util.number import getPrime as prime
from gmpy2 import powmod, invert

flag = <redacted>

p = prime(256)
q = prime(256)

n = p*q
e = 65537
d = invert(e,(p-1)*(q-1))

def encrypt(m):
    global e
    global n
    return powmod(m,e,n)
def decrypt(c):
    global d
    global n
    return powmod(c,d,n)
enc_flag = encrypt(flag)
def check(m):
    global enc_flag
    if not (m % enc_flag):
        return False
    else:
        return True

enc_flag = encrypt(flag)
print(f'Encrypted flag: {enc_flag}')
while True:
    choose = str(input('[E]ncrypt\n[D]ecrypt\n[Q]uit\n'))
    if choose == 'E':
        m = int(input('Enter your message: '))
        if check(m):
            c = encrypt(m)
            print(f'Your ciphertext: {c}')
        else:
            print('Hacker alert!!!')
    elif choose == 'D':
        c = int(input('Enter your ciphertext: '))
        if check(c):
            m = decrypt(c)
            print(f'Your plaintext: {m}')
        else:
            print('Hacker alert!!!')
    elif choose == 'Q':
        exit(0)
