#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"wavlib.h"

int main(int argc, char **argv){
	/*deals with input and output*/
	char *input_flag=NULL, *output_flag=NULL;
	ioFlags(&input_flag, &output_flag, argc, argv);

	FILE *file;
	checksInput
	if(input_flag){

		file = fopen(input_flag, "r");
		/*checks if a file was opened correclty*/
		checksFile(file);

	}
	else
		file = stdin;

	chunk info;	

	fread(info.id, sizeof(char), 4, file);
	info.id[4]='\0';	

	if(input_flag){
		fclose(file);
	}




	return 0;
}	
