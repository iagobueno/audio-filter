/*GRR20190171 Carlos Iago Bueno*/
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"wavlib.h"


/*adjust the volumn of a wavfile based on a level l*/
void adjustVolume(FILE *input, FILE *output, double level, int n){
	int16_t sample;
	int i;
	double value;

	/*checks if the value is valid*/
	level=checksLevel(level, 1, 0, 10);

	for(i=0;i<n/2;i++){
		fread(&sample, sizeof(int16_t), 1, input);

		value = sample * level;
		sample = checksSample(value);

		fwrite(&sample, sizeof(int16_t), 1, output);
	}
}

int main(int argc, char **argv){

	/*checks the possibles flags*/
	char *input_flag=NULL, *output_flag=NULL;
	double level=1;
	flags(&input_flag, &output_flag, &level, NULL, argc, argv);

	FILE *input = checksInput(input_flag);
	FILE *output = checksOutput(output_flag);

	chunk_t info;	
	readChunk(&info, input);

	copyChunk(input, output);
	adjustVolume(input, output, level, info.sub2size);	
	
	/*if files were open, they'll closed*/
	if(input_flag)
		fclose(input);
	if(output_flag)
		fclose(output);

	return 0;
}	
