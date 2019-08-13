import socket
from pprint import pprint

version = '15.0.0.0'
game_handle = 1
password = 'paseca'

flag = 'paseca{m3nt4l_d3pr3551ion_w4s_us3d_t0_m4k3_th15_t45k}'
flag_enc = ''.join(chr(int(x)) for x in ''.join(format(ord(e), 'b') for e in flag))

sock = socket.socket()
sock.bind(('127.0.0.1', 1337))
sock.listen(1)

def shutdown(reason, conn):
	print('[!] ', reason)
	conn.close()

def verify_handshake(data):
	if len(data['password']) != data['password_len'] or len(data['version']) != data['version_len'] or len(data['account_id']) != data['account_id_len'] or data['password'] != password or data['game_handle'] != game_handle or data['version'] != version:
		return False
	else:
		return True

def parse_handshake(conn):
	handshake_data = {}

	data = conn.recv(8)
	handshake_data['packet_len'] = int(data[4])
	plen = 0
	if data[0] == 22:
		if ord(conn.recv(1)) == 8:
			handshake_data['game_handle'] = ord(conn.recv(1))
			if ord(conn.recv(1)) == 18:
				plen += 3
				handshake_data['password'] = b''
				handshake_data['version'] = b''
				handshake_data['platform'] = b''
				handshake_data['account_id'] = b''
				handshake_data['unknown'] = b''

				handshake_data['password_len'] = ord(conn.recv(1))
				data = conn.recv(1)
				plen += 2
				while data[0] != 26:
					handshake_data['password'] += data
					data = conn.recv(1)
					plen += 1

				handshake_data['version_len'] = ord(conn.recv(1))
				data = conn.recv(1)
				plen += 2
				while data[0] != 34:
					handshake_data['version'] += data
					data = conn.recv(1)
					plen += 1

				data = conn.recv(1)
				plen += 1
				while data[0] != 42:
					handshake_data['platform'] += data
					data = conn.recv(1)
					plen += 1

				handshake_data['account_id_len'] = ord(conn.recv(1))
				data = conn.recv(1)
				plen += 2
				while data[0] != 42:
					handshake_data['account_id'] += data
					data = conn.recv(1)
					plen += 1

				data = conn.recv(1)
				plen += 1
				while data[0] != 42:
					handshake_data['unknown'] += data
					data = conn.recv(1)
					plen += 1

				handshake_data['password'] = handshake_data['password'].decode('ascii')
				handshake_data['version'] = handshake_data['version'].decode('ascii')
				handshake_data['platform'] = handshake_data['platform'].decode('ascii')
				handshake_data['account_id'] = handshake_data['account_id'].decode('ascii')

				if handshake_data['packet_len'] != plen:
					return shutdown('Wrong packet length', conn)

				return handshake_data

		shutdown('Parse error', conn)
	else:
		shutdown('Unsupported packet type', conn)

def main():
	while True:
		conn, addr = sock.accept()

		hs_data = parse_handshake(conn)
		if hs_data == None:
			return
		pprint(hs_data)
		if verify_handshake(hs_data):
			print('[*] Handshake success')
			conn.send(b'\x10\x00\x00\x00\x0e\x00\x00\x00\x08\x49\x10\x05\x18\x05\x20\x01\x28\x07\x30\x05\x38\x19')

			data = conn.recv(8)
			if data == b'\x73\x00\x00\x00\x00\x00\x00\x00':
				conn.send(b'\x74' + b'\x00'*7)
				data = conn.recv(8)
				if data == b'\x01\x00\x00\x00\x00\x00\x00\x00':
					conn.send(flag_enc.encode('ascii'))
					conn.close()
					print('[*] Flag sent!')

		else:
			print('[!] Fake packet or wrong credentials')
			conn.close()

if __name__ == "__main__":
	#try:
	main()
	#except:
		#print('[!] Something went wrong.')