import asyncio
from datetime import datetime
from itertools import cycle
from random import randint

g = 0x1337
p = 0xCAFEBABE

g_bytes = g.to_bytes(4, 'little', signed=False)
p_bytes = p.to_bytes(4, 'little', signed=False)
const_data = g_bytes + p_bytes

correct_login = 'fedor'
correct_password = 'rybochkin'

flag = 'paseca{4nd_h0N3Y_W1ll_FL0w_0NC3_m0r3}'
pride_flag = r'''
     _.-""""`-._ 
   ,' _-""""`-_ `.
  / ,'.-'"""`-.`. \
 | / / ,'"""`. \ \ |
| | | | ,'"`. | | | |
| | | | |   | | | | |
'''
bees = r'''
       too BEE-zy to ......    ;-_ ; \       /  _
                    ;.         .` `-. \    .:.-'
      ;.        ;.' ; \       /  `.-.`.\, /  "\
  ;-_ ; \       /` _-. \    .:.-'  '-._\/;\   /
   ` `-. \    .:.-'.-.`.\, /  "\     ,;\\\|`-' ;.         .'
    `.-.`.\, /  "\  '-._\/;\   /    (\\\.'/;-_ ; \       /  _
      '-._\/;\   /    ,;\\\|`-'   ;. `._.'  `.`-. \    .:.-'
        ,;\\\|`-' ;. (\\\.'/ .'-_ ; \       /`.-.`.\, /  "\
       (\\\.'/;-_ ; \ `._.' /  _ `-. \    .:.-''-._\/;\   /
    ;.  `._.'  .'`-. \    .:.-' `.-.`.\, /  "\   ,;\\\|`-'
;-_ ; \       / `_-.`.\, /  "\    '-._\/;\   /  (\\\.'/
 ` `-. \    .:.-' '-._\/;\   /      ,;\\\|`-' ;. `._.'   .'
  `.-.`.\, /  "\    ,;\\\|`-'  ;.  (\\\.'/;-_ ; \       /  _
    '-._\/;\   /   (\\\.'/ ;-_ ; \  `._.'/ `_`-. \    .:.-'
      ,;\\\|`-'  ;. `._.'   .'`-. \    .:.-'`.-.`.\, /  "\
     (\\\.'/ ;-_ ; \       / `_-.`.\, /  "\   '-._\/;\   /
    mx`._.'   ` `-. \    .:.-' '-._\/;\   /     ,;\\\|`-'
               `.-.`.\, /  "\    ,;\\\|`-'     (\\\.'/
                 '-._\/;\   /   (\\\.'/         `._.'
                   ,;\\\|`-'     `._.'
                  (\\\.'/
                   `._.'            ... BUZZ ?
'''
russia = r'''CHEEKI BREEKI CYKA CHEEKI BREEKI BLYAT!'''


async def xor(data, key):
    result = []
    key_data = cycle(key)
    for i in data:
        a = i ^ next(key_data)
        result.append(a)
    return bytes(result)


async def send_str(data, key, writer):
    send_data = await xor(data.encode(), key)
    writer.write(int.to_bytes(len(send_data), 2, 'little', signed=False) + send_data)
    await writer.drain()


async def handle_connection(reader, writer):
    a = randint(0xFF, 0xFFFF)
    big_a = g**a % p
    hello = (await reader.read(10)).decode()

    # print('[+] Received hello {}'.format(hello))

    if hello != 'baraban':
        writer.close()
        return

    writer.write(const_data)
    await writer.drain()

    # print('[+] Constants sent!')

    big_b_data = await reader.read(4)
    big_b = int.from_bytes(big_b_data, 'little', signed=False)
    key = big_b**a % p
    key_data = int.to_bytes(key, 4, byteorder='little', signed=False)
    # print('[+] key = {}'.format(key))

    # print('[+] B received {}'.format(big_b))

    writer.write(big_a.to_bytes(4, 'little', signed=False))
    await writer.drain()

    # print('[+] A sent!')

    await send_str('Welcome to secure PASECA server!\nEnter your login: ', key_data, writer)

    login = (await xor(await reader.read(100), key_data)).decode()

    await send_str('Enter your password: ', key_data, writer)

    password = (await xor(await reader.read(100), key_data)).decode()

    if login != correct_login or password != correct_password:
        await send_str('Incorrect credentials, bye!', key_data, writer)
        writer.close()
        return

    await send_str('Welcome FEDOR!\n1. Get flag\n2. Get PRIDE flag\n3. Get bees\n4. Make RUSSIA Greate Again\n5. Exit',
                   key_data, writer)
    while True:
        # print('[+] Welcome sent!')
        # print((await xor(await reader.read(10), key_data)).decode())
        choose = int((await xor(await reader.read(10), key_data)).decode())
        # print('[+] choose = {}'.format(choose))
        if choose == 1:
            print('{} Got flag'.format(datetime.now()))
            await send_str(flag, key_data, writer)
        elif choose == 2:
            await send_str(pride_flag, key_data, writer)
        elif choose == 3:
            await send_str(bees, key_data, writer)
        elif choose == 4:
            await send_str(russia, key_data, writer)
        else:
            writer.close()
            return

loop = asyncio.get_event_loop()
coro = asyncio.start_server(handle_connection, '0.0.0.0', 25004, loop=loop)
server = loop.run_until_complete(coro)

try:
    loop.run_forever()
except KeyboardInterrupt:
    pass

server.close()
loop.run_until_complete(server.wait_closed())
loop.close()
