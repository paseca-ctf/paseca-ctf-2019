CC=gcc
library_options=-c -Wall -Werror -fpic
so_options=-shared
current_dir=$(shell pwd)
app_name=angry
src_name=main.c

all:
	$(CC) $(library_options) check1.c
	$(CC) $(library_options) check2.c
	$(CC) $(library_options) check3.c
	$(CC) $(library_options) check4.c
	$(CC) $(library_options) check5.c
	$(CC) $(library_options) check6.c
	$(CC) $(library_options) check7.c
	$(CC) $(library_options) check8.c
	$(CC) $(library_options) check9.c
	$(CC) $(library_options) check10.c
	$(CC) $(library_options) check11.c
	$(CC) $(library_options) check12.c
	$(CC) $(library_options) check13.c
	$(CC) $(library_options) check14.c
	$(CC) $(library_options) check15.c
	$(CC) $(library_options) check16.c
	$(CC) $(library_options) check17.c
	$(CC) $(library_options) check18.c
	$(CC) $(library_options) check19.c
	$(CC) $(library_options) check20.c
	$(CC) $(library_options) check21.c
	$(CC) $(library_options) check22.c
	$(CC) $(library_options) check23.c
	$(CC) $(library_options) check24.c
	$(CC) $(library_options) check25.c
	$(CC) $(library_options) check26.c
	$(CC) $(library_options) check27.c
	$(CC) $(library_options) check28.c
	$(CC) $(library_options) check29.c
	$(CC) $(library_options) check30.c
	$(CC) $(library_options) check31.c
	$(CC) $(library_options) check32.c
	$(CC) $(library_options) check33.c
	$(CC) $(library_options) check34.c
	$(CC) $(library_options) check35.c
	$(CC) $(library_options) check36.c

	$(CC) $(so_options) -o libcheck1.so check1.o
	$(CC) $(so_options) -o libcheck2.so check2.o
	$(CC) $(so_options) -o libcheck3.so check3.o
	$(CC) $(so_options) -o libcheck4.so check4.o
	$(CC) $(so_options) -o libcheck5.so check5.o
	$(CC) $(so_options) -o libcheck6.so check6.o
	$(CC) $(so_options) -o libcheck7.so check7.o
	$(CC) $(so_options) -o libcheck8.so check8.o
	$(CC) $(so_options) -o libcheck9.so check9.o
	$(CC) $(so_options) -o libcheck10.so check10.o
	$(CC) $(so_options) -o libcheck11.so check11.o
	$(CC) $(so_options) -o libcheck12.so check12.o
	$(CC) $(so_options) -o libcheck13.so check13.o
	$(CC) $(so_options) -o libcheck14.so check14.o
	$(CC) $(so_options) -o libcheck15.so check15.o
	$(CC) $(so_options) -o libcheck16.so check16.o
	$(CC) $(so_options) -o libcheck17.so check17.o
	$(CC) $(so_options) -o libcheck18.so check18.o
	$(CC) $(so_options) -o libcheck19.so check19.o
	$(CC) $(so_options) -o libcheck20.so check20.o
	$(CC) $(so_options) -o libcheck21.so check21.o
	$(CC) $(so_options) -o libcheck22.so check22.o
	$(CC) $(so_options) -o libcheck23.so check23.o
	$(CC) $(so_options) -o libcheck24.so check24.o
	$(CC) $(so_options) -o libcheck25.so check25.o
	$(CC) $(so_options) -o libcheck26.so check26.o
	$(CC) $(so_options) -o libcheck27.so check27.o
	$(CC) $(so_options) -o libcheck28.so check28.o
	$(CC) $(so_options) -o libcheck29.so check29.o
	$(CC) $(so_options) -o libcheck30.so check30.o
	$(CC) $(so_options) -o libcheck31.so check31.o
	$(CC) $(so_options) -o libcheck32.so check32.o
	$(CC) $(so_options) -o libcheck33.so check33.o
	$(CC) $(so_options) -o libcheck34.so check34.o
	$(CC) $(so_options) -o libcheck35.so check35.o
	$(CC) $(so_options) -o libcheck36.so check36.o

	$(CC) -L$(current_dir) -Wall -o $(app_name) $(src_name) -lcheck1 -lcheck2 -lcheck3 -lcheck4 -lcheck5 -lcheck6 -lcheck7 -lcheck8 -lcheck9 -lcheck10 -lcheck11 -lcheck12 -lcheck13 -lcheck14 -lcheck15 -lcheck16 -lcheck17 -lcheck18 -lcheck19 -lcheck20 -lcheck21 -lcheck22 -lcheck23 -lcheck24 -lcheck25 -lcheck26 -lcheck27 -lcheck28 -lcheck29 -lcheck30 -lcheck31 -lcheck32 -lcheck33 -lcheck34 -lcheck35 -lcheck36 
clean:
	$(shell rm -rf *.o)