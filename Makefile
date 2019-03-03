CC=gcc
CFLAGS=-W -Wall -g
LDFLAGS=
EXEC=

all: projet

projet: main.o
	$(CC) -o projet *.o	-lm

main.o: main.c lectureFichiers.o site.o harversine.o procheVoisin.o gestionItineraire.o
	$(CC) -c -o main.o main.c $(CFLAGS)

site.o: site.h site.c
	$(CC) -c -o site.o site.c $(CFLAGS)

lectureFichiers.o: lectureFichiers.c site.o
	$(CC) -c -o lectureFichiers.o lectureFichiers.c $(CFLAGS)

harversine.o: haversine.h haversine.c
	$(CC) -c -o haversine.o haversine.c $(CFLAGS)

procheVoisin.o: procheVoisin.h procheVoisin.c
	$(CC) -c -o procheVoisin.o procheVoisin.c $(CFLAGS)

gestionItineraire.o: gestionItineraire.h gestionItineraire.c
	$(CC) -c -o gestionItineraire.o gestionItineraire.c $(CFLAGS)

clean:
	rm *.o
	rm projet


	 	
