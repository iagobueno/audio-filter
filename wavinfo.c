#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"wavlib.h"

int main(int argc, char **argv){
	/*deals with input and output*/
	char *input_flag=NULL, *output_flag=NULL;
	ioFlags(&input_flag, &output_flag, argc, argv);

	FILE *input = checksInput(input_flag);
	FILE *output = checksOutput(output_flag);

	chunk_t info;	
	readChunk(&info, input);
	printChunk(&info, output);

	if(input_flag)
		fclose(input);

	if(output_flag)
		fclose(output);

	return 0;
}	
