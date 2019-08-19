from Crypto.Cipher import AES

file_in = open("out.bin", "rb")
nonce, tag, ciphertext = [ file_in.read(x) for x in (16, 16, -1) ]

key = b'youareontherightway'[:16]
cipher = AES.new(key, AES.MODE_EAX, nonce)
data = cipher.decrypt_and_verify(ciphertext, tag)
out = open('solved.png', 'wb')
out.write(data)
out.close()
