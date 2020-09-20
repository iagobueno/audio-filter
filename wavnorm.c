/*GRR20190171 Carlos Iago Bueno*/
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"wavlib.h"

/*finds a constant that approaches the greatest value to MAX*/
float findConstant(int16_t great){
	float c;
	for(c=1.001; great*c < MAX;c+=0.001);

	return (c-0.001);
}

/*normaziles a wavile*/
void normalizes(FILE *input, FILE *output, int n){

	int16_t *sample;
	sample = malloc( (n/2) * sizeof(int16_t));
	if(!sample){
		perror("memory wasn't reserved correctly");
		exit(2);
	}

        int i;

        for(i=0;i<n/2;i++)
                fread(&sample[i], sizeof(int16_t), 1, input);

	int16_t great=findGreatest(sample, n/2);
	float c=findConstant(great);	


        for(i=0;i<n/2;i++){
                sample[i] = (int16_t)(c * sample[i]);
                fwrite(&sample[i], sizeof(int16_t), 1, output);
        }	

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
	normalizes(input, output, info.sub2size);	
	
	/*if files were open, they'll closed*/
	if(input_flag)
		fclose(input);
	if(output_flag)
		fclose(output);


	return 0;
}	
