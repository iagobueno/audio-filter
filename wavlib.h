/*GRR20190171 Carlos Iago Bueno*/
#ifndef WAVLIB_H
#define WAVLIB_H
#define MAX 32767
#define MIN -32767
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
void flags(char **input_flag, char **output_flag, double *level, double *delay, int argc, char **argv);

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

/*checks if a sample has passed the wave limit and ajust it*/
int16_t checksSample(int16_t sample, double level);

/*checks if level is a acceptable value*/
double checksLevel(double level);

/*adjust the volumn of a wavfile based on a level l*/
void adjustVolume(FILE *input, FILE *output, double level, int n);

/*finds the greatest value into a array*/
int16_t findGreatest(int16_t *array, int size);

/*finds a constant that approaches the greatest value to MAX*/
float findConstant(int16_t great);

/*normaziles a wavile*/
void normalizes(FILE *input, FILE *output, int n);

void reverses(FILE *input, FILE *output, int n);

void echoes(FILE *input, FILE *output, double level, double delay, int n);

#endif
