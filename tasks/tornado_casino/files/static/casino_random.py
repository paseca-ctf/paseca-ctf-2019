w = 32

n = 624
INDEX = n + 1

m = 397
r = 31

a = 2567483615

u = 11
d = 4294967295

s = 7
b = 2636928640

t = 15
c = 4022730752

l = 18
f = 1812433253

mt = [0 for i in range(n)]
l_m, u_m = 4294967295, 0

def init_state(seed):
    mt[0] = seed
    for i in range(1, n):
        mt[i] = ( f * ( mt[i-1] ^ (mt[i-1] >> (w - 2) ) ) ) & 0xffffffff
        
def ret_state():
    global INDEX
    if INDEX >= n:
        twist()
        INDEX = 0

    y = mt[INDEX]
    y ^= ((y >> u) & d)
    y ^= ((y << t) & c)
    y ^= ((y << s) & b)
    y ^= (y >> l)
    y &= 0xffffffff
    INDEX += 1

    return y

def twist():
    for i in range(n):
        X = (mt[i] & u_m) + (mt[(i+1) % n] & l_m)
        Xa = X >> 1
        if (X % 2):
            Xa ^= a
        mt[i] = mt[(i+m) % n] ^ Xa
