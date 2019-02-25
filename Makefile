CC=gcc
CFLAGS=-W -Wall -g
LDFLAGS=
EXEC=

all: projet

projet: main.o
	$(CC) -o projet *.o	-lm

main.o: main.c lectureFichiers.o site.o harversine.o
	$(CC) -c -o main.o main.c $(CFLAGS)

site.o: site.h site.c
	$(CC) -c -o site.o site.c $(CFLAGS)

lectureFichiers.o: lectureFichiers.c site.o
	$(CC) -c -o lectureFichiers.o lectureFichiers.c $(CFLAGS)

harversine.o: haversine.h haversine.c
	$(CC) -c -o haversine.o haversine.c $(CFLAGS)

clean:
	rm *.o


	 	
