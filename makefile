#GRR20190171 Carlos Iago Bueno

CC = gcc
CFLAGS = -Wall
LIBS =
OBJ = wavlib.o
DEPS = wavli.h

all: wavlib.o wavinfo wavvol wavnorm wavecho wavrev wavwide wavcat wavmix

wavmix: wavmix.o wavlib.o
	$(CC) $(CFLAGS) $(OBJ) wavmix.o -o wavmix

wavcat: wavcat.o wavlib.o
	$(CC) $(CFLAGS) $(OBJ) wavcat.o -o wavcat

wavwide: wavwide.o wavlib.o
	$(CC) $(CFLAGS) $(OBJ) wavwide.o -o wavwide

wavrev: wavrev.o wavlib.o
	$(CC) $(CFLAGS) $(OBJ) wavrev.o -o wavrev

wavecho: wavecho.o wavlib.o
	$(CC) $(CFLAGS) $(OBJ) wavecho.o -o wavecho

wavnorm: wavnorm.o wavlib.o
	$(CC) $(CFLAGS) $(OBJ) wavnorm.o -o wavnorm

wavvol: wavvol.o wavlib.o
	$(CC) $(CFLAGS) $(OBJ) wavvol.o -o wavvol

wavinfo: wavinfo.o wavlib.o
	$(CC) $(CFLAGS) $(OBJ) wavinfo.o -o wavinfo

wavlib.o: wavlib.c wavlib.h

clean:
	-rm -f *.o

purge:
	-rm -f *.o wavinfo wavvol wavnorm wavrev wavecho wavwide wavcat wavmix
