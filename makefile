all: binary.o common.o name.o principals.o title.o main.o
	gcc binary.o common.o name.o principals.o title.o main.o -o a3

binary.o: binary.c common.h
	gcc -Wall -ansi -pedantic binary.c -c -o binary.o
	
common.o: common.c common.h
	gcc -Wall -ansi -pedantic common.c -c -o common.o

name.o: name.c binary.h common.h name.h
	gcc -Wall -ansi -pedantic name.c -c -o name.o

principals.o: principals.c binary.h common.h
	gcc -Wall -ansi -pedantic principals.c -c -o principals.o
	
title.o: title.c
	gcc -Wall -ansi -pedantic title.c -c -o title.o
	
main.o: main.c binary.h common.h name.h principals.h title.h
	gcc -Wall -ansi -pedantic main.c -c -o main.o

clean:
	rm *.o
