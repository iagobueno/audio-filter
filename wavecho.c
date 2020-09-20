/*GRR20190171 Carlos Iago Bueno*/
#include"wavlib.h"
#include<stdlib.h>

void echoes(FILE *input, FILE *output, double level, double delay, int n){
	
	int16_t *sample;
        sample = malloc( (n/2) * sizeof(int16_t));
        if(!sample){
                perror("memory wasn't reserved correctly");
                exit(2);
        }

	int i;
	for(i=0;i<n/2;i++)
                fread(&sample[i], sizeof(int16_t), 1, input);

	/*checks if the value is valid*/
	level=checksLevel(level, 0.5, 0, 1);
	/*adjust delay*/
	delay*=100;

	for(i=delay;i<n/2;i++){
		int index = (int) (i - (delay));
                sample[i] = (int16_t)(sample[i] + (level * sample[index]));
                fwrite(&sample[i], sizeof(int16_t), 1, output);
        }

	free(sample);
        sample=NULL;
}

int main(int argc, char **argv){

	/*checks the possibles flags*/
	char *input_flag=NULL, *output_flag=NULL;
	double level=1, delay=1;
	flags(&input_flag, &output_flag, &level, &delay, argc, argv);

	FILE *input = checksInput(input_flag);
	FILE *output = checksOutput(output_flag);

	chunk_t info;	
	readChunk(&info, input);

	copyChunk(input, output);
	echoes(input, output, level, delay, info.sub2size);	
	
	/*if files were open, they'll closed*/
	if(input_flag)
		fclose(input);
	if(output_flag)
		fclose(output);


	return 0;
}	
