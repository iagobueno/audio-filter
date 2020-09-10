#ifndef WAVLIB_H
#define WAVLIB_H
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<inttypes.h>

struct chunk_t{
	char id[5];
	char format[5];
	char sub1id[5];
	char sub2id[5];
	uint16_t audioformat, nchannels, blockalign, bitsps;
	uint32_t size, sub1size, samplerate, byterate, sub2size, bytesps, samplespc;
};
typedef struct chunk_t chunk_t;

/*checks if a file was opened correclty*/
void checksFile(FILE *file);

void ioFlags(char **, char **, int, char  **);

/*checks if the input comes from stdin or by flag*/
FILE *checksInput(char *);

void readChunk(chunk_t *info, FILE *file);

void printChunk(chunk_t *info);

#endif
