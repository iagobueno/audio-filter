/*GRR20190171 Carlos Iago Bueno*/
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"wavlib.h"

void reverses(FILE *input, FILE *output, int n){

	int16_t *sample;
        sample = malloc( (n/2) * sizeof(int16_t));
        if(!sample){
                perror("memory wasn't reserved correctly");
                exit(2);
        }

	int i;

        for(i=0;i<n/2;i++)
                fread(&sample[i], sizeof(int16_t), 1, input);

	for(i=n/2;i>0;i--)
		fwrite(&sample[i], sizeof(int16_t), 1, output);

	free(sample);
        sample=NULL;
}

int main(int argc, char **argv){

	/*checks the possibles flags*/
	char *input_flag=NULL, *output_flag=NULL;
	flags(&input_flag, &output_flag, NULL, NULL, argc, argv);

	FILE *input = checksInput(input_flag);
	FILE *output = checksOutput(output_flag);

	chunk_t info;	
	readChunk(&info, input);

	copyChunk(input, output);
	reverses(input, output, info.sub2size);	
	
	/*if files were open, they'll closed*/
	if(input_flag)
		fclose(input);
	if(output_flag)
		fclose(output);


	return 0;
}	
