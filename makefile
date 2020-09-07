#GRR20190171 Carlos Iago Bueno

CC = gcc
CFLAGS = -Wall
LIBS = 
OBJ = wavinfo.o wavlib.o
DEPS = wavlib.h

wavinfo: wavinfo.o wavlib.o
	$(CC) $(OBJ) -o wavinfo

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	-rm -f $(OBJ)

purge:
	-rm -f wavinfo
