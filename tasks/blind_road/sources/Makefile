CC=gcc
outname=../../../challenge
source=main.c
cc_flags=-fno-stack-protector -no-pie -O0 -masm=intel

all:
	gcc $(source) $(cc_flags) -o $(outname)

32:
	gcc $(source) $(cc_flags) -m32 -o $(outname)

64:
	gcc $(source) $(cc_flags) -o $(outname)
	