#ifndef WAVLIB_H
#define WAVLIB_H
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct chunk{
	char id[5];
};
typedef struct chunk chunk;

/*checks if a file was opened correclty*/
void checksFile(FILE *file);

void ioFlags(char **, char **, int, char  **);

void readChunk(chunk *info);

#endif
