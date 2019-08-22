from gmpy2 import powmod, invert
from Crypto.Util.number import getPrime as prime
#paseca{pr1v4t3_key_4s_padd1ng_gr34t_1dea}
flag = 240043647915381768642014611132941598130134768642264866996663345152365801782359461453590056459919741
alls_bad = True
while alls_bad:
    p = prime(512)
    q = prime(512)

    n = p*q
    t = (p-1)*(q-1)

    e = 0b10001
    try:
        d = invert(e,t)

        public = (e,n)
        private = (d,n)
        alls_bad = False
        enc_flag = powmod(flag, e, n)
    except:
        pass


def pad(m):
    global p
    if p.bit_length() + m.bit_length() < n.bit_length():
        return True, (p << m.bit_length()) + m
    else:
        return False, 'Error: message too big'
def unpad(m):
    global p
    
    return m & (2 ** (m.bit_length() - p.bit_length()) - 1)


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
        
