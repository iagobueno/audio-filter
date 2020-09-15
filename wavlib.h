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
	uint32_t size, sub1size, samplerate, byterate, sub2size;
};
typedef struct chunk_t chunk_t;

/*checks if a file was opened correclty*/
void checksFile(FILE *file);

/*checks and treat the possibles flags*/
void flags(char **input_flag, char **output_flag, float *level, int argc, char **argv);

/*returns a file that points to the flag argument or to stdin*/
FILE *checksInput(char *input_flag);

/*returns a file that points to the flag argument or to stdout*/
FILE *checksOutput(char *output_flag);

void readChunk(chunk_t *info, FILE *file);

void writeChunk(chunk_t *info, FILE *file);

/*prints the chunk from a wav file*/
void printChunk(chunk_t *info, FILE *file);

/*copy the input's chunk to the output's chunk*/
void copyChunk(FILE *input, FILE *output);

/*adjust the volumn of a wavfile based on a level l*/
void adjustVolume(FILE *input, FILE *output, float level, int n);

#endif
