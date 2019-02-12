CC=gcc
CFLAGS=-W -Wall -g
LDFLAGS=
EXEC=

all: projet

projet: main.o
	$(CC) -o projet *.o	

main.o: main.c lectureFichiers.o site.o
	$(CC) -c -o main.o main.c $(CFLAGS) 

site.o: site.h site.c
	$(CC) -c -o site.o site.c $(CFLAGS)

lectureFichiers.o: lectureFichiers.c site.o
	$(CC) -c -o lectureFichiers.o lectureFichiers.c $(CFLAGS)

clean:
	rm *.o


	 	
