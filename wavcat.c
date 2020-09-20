/*GRR20190171 Carlos Iago Bueno*/
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"wavlib.h"

/*prints the chunk from a wav file*/
void printChunk(chunk_t *info, FILE *file){
        fprintf(file,"riff tag	(4 bytes): \"%.4s\"\n", info->id);
        fprintf(file,"riff size	(4 bytes): %u\n", info->size);
        fprintf(file,"wave tag	(4 bytes): \"%.4s\"\n", info->format);
        fprintf(file,"form tag	(4 bytes): \"%.4s\"\n", info->sub1id);
        fprintf(file,"fmt_size	(4 bytes): %u\n", info->sub1size);
        fprintf(file,"audio_format	(2 bytes): %u\n", info->audioformat);
        fprintf(file,"num_channels	(2 bytes): %u\n", info->nchannels);
        fprintf(file,"sample_rate	(4 bytes): %u\n", info->samplerate);
        fprintf(file,"byte_rate	(4 bytes): %u\n", info->byterate);
        fprintf(file,"block_align	(2 bytes): %u\n", info->blockalign);
        fprintf(file,"bits_per_sample	(2 bytes): %u\n", info->bitsps);
        fprintf(file,"data tag	(4 bytes): \"%.4s\"\n", info->sub2id);
        fprintf(file,"data size	(4 bytes): %u\n", info->sub2size);
        fprintf(file,"bytes per sample:	 : %u\n", info->bitsps/8);
        fprintf(file,"samples per channel	 : %u\n", info->sub2size/info->blockalign);
}

void concatFiles(FILE **files, FILE *output, chunk_t *info, int n){
	int16_t sample;	

	int i, j;
	for(j=0; j<n ; j++){
		for(i=0; i <info[0].sub2size/2; i++){
			fread(&sample, sizeof(int16_t), 1, files[j]);
			fwrite(&sample, sizeof(int16_t), 1, output);
		}
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

	aux.size = 0;
	aux.sub2size = 0;
	rewind(files[0]);

	chunk_t *info;
	info = malloc( n * sizeof(chunk_t));

	int i;
	for(i=0;i<n;i++){
		readChunk(&info[i], files[i]);
		aux.size = aux.size + info[i].size;
		aux.sub2size = aux.sub2size + info[i].sub2size;
	}

	fwrite(&aux, sizeof(chunk_t), 1, output);
	concatFiles(files, output, info, n);
	
	/*if files were open, they'll closed*/
	if(output_flag)
		fclose(output);


	return 0;
}	
