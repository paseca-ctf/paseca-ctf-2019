from sympy import prime
from random import getrandbits
from Crypto.Util.number import isPrime
from gmpy2 import powmod

def primorial(n):
    P = 1
    for i in range(1, n + 1):
        P *= prime(i)
    return P

def fast_prime(): #fastest method to generate 256 bit prime number
    prime = 4
    M = primorial(39) #Using 39 to get 256 <= prime_bits <= 960
    while not isPrime(prime):#ofc u can say "lol pycrypto has getPrime"
                             #but my fast_prime is faster than getPrime
        a = getrandbits(62)  #hardcode some
        k = getrandbits(37)  #fast parameters
        prime = k*M + powmod(0x10001, a, M)
    return prime

p = fast_prime()
q = fast_prime()
assert p != q, 'Wow'

n = p*q
e = 0x10001
public_key = (e, n)

# public_key = (65537, 2533518484273416680526744527076070415105694309505300600842191515956287023049872818275864738915507865375824167505682003696379926562543280251434287750844677)
# c = 129004287495003585102707258242341500697789427644709664498422921557824879930305360888810887386464959697534364343822749974218601464578445454172199855198387
