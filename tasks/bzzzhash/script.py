flag = int(b'<there was flag>'.hex(),16)
def really_good_hash(text,n):
    hashsum = 0
    for i in range(n+1):
        hashsum+=i*text**i
    return hashsum
checksum = really_good_hash(text,2**14)
checksum = fast_hash(text,2**14)
f = open('checksum','w')
print(checksum,file = f)
