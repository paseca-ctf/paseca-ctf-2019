import asyncio
from random import randint
from itertools import cycle


async def xor(data, key):
    result = []
    key_data = cycle(key)
    for i in data:
        a = i ^ next(key_data)
        result.append(a)
    return bytes(result)


async def send_str(data, key, writer):
    send_data = await xor(data.encode(), key)
    writer.write(send_data)


async def client(loop):

    reader, writer = await asyncio.open_connection('5.200.53.16', 24004,
                                                   loop=loop)

    writer.write('baraban'.encode())

    g = int.from_bytes(await reader.read(4), 'little', signed=False)
    p = int.from_bytes(await reader.read(4), 'little', signed=False)
    b = randint(0xFF, 0xFFFF)
    big_b = g ** b % p
    print('[+] p = {}, g = {}'.format(hex(p), hex(g)))
    writer.write(int.to_bytes(big_b, 4, 'little', signed=False))
    big_a = int.from_bytes(await reader.read(4), 'little', signed=False)
    print('[+] A received!')
    key = big_a ** b % p
    print('[+] key = {}'.format(key))
    key_data = int.to_bytes(key, 4, byteorder='little', signed=False)

    while True:
        data_len = int.from_bytes(await reader.read(2), 'little', signed=False)
        data = await xor(await reader.read(data_len), key_data)
        print(data.decode())
        await send_str(input(), key_data, writer)

    print('Close the socket')
    writer.close()


loop = asyncio.get_event_loop()
loop.run_until_complete(client(loop))
loop.close()
