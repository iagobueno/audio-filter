#GRR20190171 Carlos Iago Bueno

CC = gcc
CFLAGS = -Wall
LIBS = 
OBJ = wavlib.o
DEPS = wavlib.h

wavnorm: wavnorm.o wavlib.o
	$(CC) wavnorm.o $(OBJ) -o wavnorm

wavvol: wavvol.o wavlib.o
	$(CC) wavvol.o $(OBJ) -o wavvol

wavinfo: wavinfo.o wavlib.o
	$(CC) wavinf.o $(OBJ) -o wavinfo

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	-rm -f *.o

purge:
	-rm -f *.o wavinfo wavvol
