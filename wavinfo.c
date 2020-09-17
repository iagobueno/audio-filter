/*GRR20190171 Carlos Iago Bueno*/
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"wavlib.h"

int main(int argc, char **argv){

	/*checks the possibles flags*/
	char *input_flag=NULL, *output_flag=NULL;
	flags(&input_flag, &output_flag, NULL, NULL, argc, argv);

	FILE *input = checksInput(input_flag);
	FILE *output = checksOutput(output_flag);

	/*reads and print a chunk from a wavfile*/
	chunk_t info;	
	readChunk(&info, input);
	printChunk(&info, output);

	/*if files were open, they'll closed*/
	if(input_flag)
		fclose(input);
	if(output_flag)
		fclose(output);

	return 0;
}	
