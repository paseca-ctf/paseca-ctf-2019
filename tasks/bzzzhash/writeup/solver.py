
def fast_hash(text,n):
    return (n*bin_pow(text,n+2)-(n+1)*bin_pow(text,n+1)+text)//(text-1)**2
def bin_pow(a,b):
    res = 1
    while b:
        if b & 1:
            res*=a
            b-=1
        else:
            a*=a
            b>>=1
    return res
f = open('checksum','r')
s = f.read()
print(len(s))
checksum = int(s)
print('starting solving')
def solve(checksum):
    i = 0
    j = 10**97
    while (j-i)>1:
        if fast_hash((i+j)//2,2**14)>checksum:
            i,j = i,(i+j)//2
        else:
            i,j = (i+j)//2,j
        print(i,j)
    return i
print(solve(checksum))
