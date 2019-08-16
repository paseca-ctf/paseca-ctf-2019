from Crypto.Util.number import getPrime
from factordb.factordb import FactorDB
from gmpy2 import powmod
from math import log, log10, log2, ceil
from random import randint

flag = 'paseca{bzbz_4ll_b335_l0v3_m47h_4nd_1_l0v3_my_p453c4}'
weights = [10**15] * len(flag)
for j in range(7):
    weights[j] = (10 ** 7) * (j + 1) // 5


def prime_factors(n):
    f = FactorDB(n)
    f.connect()
    return f.get_factor_list()


def phi(n):
    a = n
    for factor in prime_factors(n):
        a -= a // factor
    return a


def gen(weight):
    m = getPrime(ceil(log2(weight)))
    g = randint(10, 1000)

    c = phi(m)

    while True:
        ex = False
        for q in prime_factors(c):
            a = powmod(g, c//q, m)
            if a == 1:
                ex = True
                break
        if not ex:
            break
        else:
            g += 1

    return g, m


def brute_solve(g, a, m):
    for x in range(m):
        if powmod(g, x, m) == a:
            return x


def gen_data():
    gk = []
    mk = []
    xk = []
    ak = []
    for i in range(len(flag)):
        g, m = gen(weights[i])
        x = randint(m // 10, m)
        x_data = bytearray(x.to_bytes(8, 'little', signed=False))
        x_data[0] = ord(flag[i])
        x = int.from_bytes(x_data, 'little', signed=False)
        a = int(powmod(g, x, m))
        gk.append(g)
        mk.append(m)
        xk.append(x)
        ak.append(a)
        print('g {} m {} x {} a {}'.format(g, m, x, a))

    print(gk)
    print(mk)
    print(ak)
    print(xk)


def main():
    gen_data()


if __name__ == '__main__':
    main()
