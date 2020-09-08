#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"wavlib.h"

int main(int argc, char **argv){
	/*deals with input and output*/
	char *input_flag=NULL, *output_flag=NULL;
	ioFlags(&input_flag, &output_flag, argc, argv);

	FILE *file = checksInput(input_flag);

	chunk info;	
	readChunk(&info, file);

	printChunk(&info);

	if(input_flag){
		fclose(file);
	}

	return 0;
}	
