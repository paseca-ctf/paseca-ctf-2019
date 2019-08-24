#!/usr/bin/env python3
from Crypto import Random
from Crypto.Cipher import AES
import base64
import sys
import hashlib
import binascii

class AESCipher(object):

    def __init__(self, key):
        self.bs = 32
        self.key = hashlib.sha256(key.encode()).digest()

    def encrypt(self, raw):
        raw = self._pad(raw)
        iv = Random.new().read(AES.block_size)
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        return base64.b64encode(iv + cipher.encrypt(raw))

    def decrypt(self, enc):
        enc = base64.b64decode(enc)
        iv = enc[:AES.block_size]
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        return self._unpad(cipher.decrypt(enc[AES.block_size:])).decode('utf-8')

    def _pad(self, s):
        return s + (self.bs - len(s) % self.bs) * bytes([self.bs - len(s) % self.bs])

    @staticmethod
    def _unpad(s):
        return s[:-int.from_bytes(s[len(s)-1:], "big")]

def decrypt(data):
    n = 'totalpasecatotalcrypto324'
    a = AESCipher(n)
    return a.decrypt(data)
	
if __name__ == "__main__":
    enc_flag = sys.argv[1] # eg png pic
    magic = sys.argv[2] # PNG
    with open(enc_flag, 'rb') as f:
        d = f.read()
    while magic != d[:len(magic)]:
        print("STEP")
        d = decrypt(d)
        print(binascii.hexlify(d))
    print(d)
