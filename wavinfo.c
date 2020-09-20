/*GRR20190171 Carlos Iago Bueno*/
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
