from pwn import *
sh = connect('localhost',1488)
bet = 1
gotcha = 0
maxbet = 0
def mainloop():
	global bet
	global maxbet
	global gotcha
	sh.readuntil('?\n')
	if gotcha>=4000:
		sh.sendline('flag')
		(sh.readline())
		(sh.readline())
		sh.readuntil('?\n')
		sh.sendline('flag')
		print(sh.readline().strip(),maxbet)
		quit()
	sh.sendline('1')
	sh.readuntil('36.\n')
	sh.sendline(' '.join([str(i) for i in range(1,19)]))
#	print(' '.join([str(i) for i in range(1,19)]))
	st = sh.readline()
	sh.sendline(str(bet))
	st = sh.readline()
#	print(st)
	st = sh.readline()
#	print(st)
	if 'lose' in st:
		bet*=2
	else:
		maxbet = max(bet,maxbet)	
#		sh.interactive()
		sh.sendline('Gotcha')
		(sh.readline())
		gotcha +=1
		bet = 1
while True:
	mainloop()
