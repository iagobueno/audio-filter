/*GRR20190171 Carlos Iago Bueno*/
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"wavlib.h"

void mixFiles(FILE **files, FILE *output, chunk_t *info, int nfiles, int nsamples){
	int16_t sample;
	double sample_sum;	

	int j, i;
	for(j=0;j<nsamples/2;j++){

		for(i=0, sample_sum = 0;i<nfiles;i++){
			fread(&sample, sizeof(int16_t), 1, files[i]);
			if(j < info[i].sub2size)
				sample_sum+= sample;
		}

		sample = checksSample(sample_sum);
		fwrite(&sample, sizeof(int16_t), 1, output);
	}
}

int main(int argc, char **argv){

	/*checks the possibles flags*/
	char *output_flag=NULL;
	flags(NULL, &output_flag, NULL, NULL, argc, argv);

	FILE *output = checksOutput(output_flag);
	int n = numbersOfFiles(output,argc); 
	FILE **files = openFiles(n, argv);

	chunk_t aux;	
	readChunk(&aux, files[0]);
	rewind(files[0]);

	chunk_t *info;
	info = malloc( n * sizeof(chunk_t));
	/*checks if memory was reserved correctly*/
        if(!info){
                perror("memory wasn't reserved correctly");
                exit(2);
        }

	int i;
	for(i=0;i<n;i++){
		readChunk(&info[i], files[i]);

		if(info[i].nchannels != aux.nchannels){
			perror("erro: different numbers of channels\n");
			exit(1);
		}

		if(info[i].size > aux.size){
			aux.size = info[i].size;	
			aux.sub2size = info[i].sub2size;
		}
	}

	fwrite(&aux, sizeof(chunk_t), 1, output);
	mixFiles(files, output, info, n, aux.sub2size);
	
	/*if files were open, they'll closed*/
	if(output_flag)
		fclose(output);

	for(i=0;i<n;i++)
		fclose(files[i]);

	free(info);
	info = NULL;

	return 0;
}	
