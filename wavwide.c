/*GRR20190171 Carlos Iago Bueno*/
#include"wavlib.h"
#include<stdlib.h>

/**/
void amplifyStereo(FILE *input, FILE *output, double level, int n){
	
	int16_t *sample, *sample2;
	sample = malloc( (n/4) * sizeof(int16_t));
        if(!sample){
                perror("memory wasn't reserved correctly");
                exit(2);
        }

	sample2 = malloc( (n/4) * sizeof(int16_t));
        if(!sample2){
                perror("memory wasn't reserved correctly");
                exit(2);
        }

	int i;
	for(i=0;i<n/2;i++){
                fread(&sample[i], sizeof(int16_t), 1, input);
                fread(&sample2[i], sizeof(int16_t), 1, input);
	}

	double value;
	int16_t diff;	
	for(i=0;i<n/4;i++){
		diff = sample[i] - sample2[i]; /*calculates diff*/

		value = (sample[i] + level * diff);
		sample[i] = checksSample(value); /*checks if value didn't pass the wave limit*/

		value = (sample2[i] - level * diff);
		sample2[i] = checksSample(value);

                fwrite(&sample[i], sizeof(int16_t), 1, output);
                fwrite(&sample2[i], sizeof(int16_t), 1, output);
        }
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
	amplifyStereo(input, output, level, info.sub2size);	
	
	/*if files were open, they'll closed*/
	if(input_flag)
		fclose(input);
	if(output_flag)
		fclose(output);


	return 0;
}	
