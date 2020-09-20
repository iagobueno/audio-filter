/*GRR20190171 Carlos Iago Bueno*/
#ifndef WAVLIB_H
#define WAVLIB_H
#define MAX 32767
#define MIN -32767
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<inttypes.h>

struct chunk_t{
	char id[4];
	uint32_t size;
	char format[4];
	char sub1id[4];
	uint32_t sub1size;
	uint16_t audioformat;
	uint16_t nchannels;
	uint32_t samplerate;
	uint32_t byterate;
	uint16_t blockalign;
	uint16_t bitsps;
	char sub2id[4];
	uint32_t sub2size;
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

/*reads a chunk of a wavfile and turns it printable*/
void readChunk(chunk_t *info, FILE *file);

/*copy the input's chunk to the output's chunk*/
void copyChunk(FILE *input, FILE *output);

/*checks if a sample has passed the wave limit and ajust it*/
int16_t checksSample(double sample);

/*checks if level is a acceptable value*/
double checksLevel(double level, double standart, double lower, double higher);

/*finds the greatest value into a array*/
int16_t findGreatest(int16_t *array, int size);

FILE **openFiles(int n, char **argv);

int numbersOfFiles(FILE *output, int argc);

#endif
