from itertools import cycle

g = 0x1337
p = 0xcafebabe
big_a = int.from_bytes([0xd7, 0x6c, 0xda, 0x4b], 'little', signed=False)
big_b = int.from_bytes([0x63, 0x27, 0xad, 0x29], 'little', signed=False)

login = [0x25, 0x4f, 0x2a, 0xdf, 0x31]
password = [0x31, 0x53, 0x2c, 0xdf, 0x20, 0x42, 0x25, 0xd9, 0x2d]


def xor(data, key):
    result = []
    key_data = cycle(key)
    for i in data:
        a = i ^ next(key_data)
        result.append(a)
    return bytes(result)


def main():
    for i in range(p):
        if g ** i % p == big_a:
            a = i
            print('[+] a found!')
            break

    key = big_b ** a % p
    key_data = int.to_bytes(key, 4, 'little', signed=False)

    print(xor(login, key_data).decode())
    print(xor(password, key_data).decode())


if __name__ == '__main__':
    main()
