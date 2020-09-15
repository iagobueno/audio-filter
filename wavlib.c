#include"wavlib.h"

/*checks if a file was opened correclty*/
void checksFile(FILE *file){
        if(!file){
                perror("file wasn't opened correctly");
                exit(1);
        }
}

/*deals the used flags*/
void flags(char **input_flag, char **output_flag, float *level, int argc, char **argv){
	int flag;
	opterr=0;

	for(;(flag=getopt(argc,argv,"i:o:l:")) != -1;){
		if(flag =='i')
			*input_flag=optarg;
		if(flag =='o')
			*output_flag=optarg;
		if(flag =='l')
			*level=atof(optarg);
		
	}
	
}

/*returns a file that points to the flag argument or to stdin*/
FILE *checksInput(char *input_flag){
	FILE *file=NULL;
	if(input_flag)
		file = fopen(input_flag, "r");
	else
                file = stdin;

	checksFile(file);

	return file;
}

/*returns a file that points to the flag argument or to stdout*/
FILE *checksOutput(char *output_flag){
        FILE *file=NULL;
        if(output_flag)
                file = fopen(output_flag, "w");
        else
                file = stdout;

        checksFile(file);

        return file;
}

/*reads wav's file chunk*/
void readChunk(chunk_t *info, FILE *file){
	fread(info->id, sizeof(char), 4, file);
        info->id[4]='\0';

	fread(&info->size, sizeof(uint32_t), 1, file);

	fread(info->format, sizeof(char), 4, file);
        info->format[4]='\0';

	fread(info->sub1id, sizeof(char), 4, file);
        info->sub1id[4]='\0';

	fread(&info->sub1size, sizeof(uint32_t), 1, file);

	fread(&info->audioformat, sizeof(uint16_t), 1, file);

	fread(&info->nchannels, sizeof(uint16_t), 1, file);

	fread(&info->samplerate, sizeof(uint32_t), 1, file);

	fread(&info->byterate, sizeof(uint32_t), 1, file);

	fread(&info->blockalign, sizeof(uint16_t), 1, file);

	fread(&info->bitsps, sizeof(uint16_t), 1, file);

	fread(info->sub2id, sizeof(char), 4, file);
        info->sub2id[4]='\0';

	fread(&info->sub2size, sizeof(uint32_t), 1, file);

	rewind(file);
}

/*prints the chunk from a wav file*/
void printChunk(chunk_t *info, FILE *file){
	fprintf(file,"riff tag	(4 bytes): \"%s\"\n", info->id);
	fprintf(file,"riff size	(4 bytes): %u\n", info->size);
	fprintf(file,"wave tag	(4 bytes): \"%s\"\n", info->format);
	fprintf(file,"form tag	(4 bytes): \"%s\"\n", info->sub1id);
	fprintf(file,"fmt_size	(4 bytes): %u\n", info->sub1size);
	fprintf(file,"audio_format	(2 bytes): %u\n", info->audioformat);
	fprintf(file,"num_channels	(2 bytes): %u\n", info->nchannels);
	fprintf(file,"sample_rate	(4 bytes): %u\n", info->samplerate);
	fprintf(file,"byte_rate	(4 bytes): %u\n", info->byterate);
	fprintf(file,"block_align	(2 bytes): %u\n", info->blockalign);
	fprintf(file,"bits_per_sample	(2 bytes): %u\n", info->bitsps);
	fprintf(file,"data tag	(4 bytes): \"%s\"\n", info->sub2id);
	fprintf(file,"data size	(4 bytes): %u\n", info->sub2size);
	fprintf(file,"bytes per sample	 : %u\n", info->bitsps/8);
	fprintf(file,"samples per channel	 : %u\n", info->sub2size/info->blockalign);
}

/*copy the input's chunk to the output's chunk*/
void copyChunk(FILE *input, FILE *output){
	chunk_t info;
	fread(&info, sizeof(chunk_t), 1, input);
	fwrite(&info, sizeof(chunk_t), 1, output);
}

/*adjust the volumn of a wavfile based on a level l*/
void adjustVolume(FILE *input, FILE *output, float level, int n){
	int16_t sample;
	int i;

	if(!level)
		level=1;

	for(i=0;i<n/2;i++){
		fread(&sample, sizeof(int16_t), 1, input);
		sample = sample * level;
		fwrite(&sample, sizeof(int16_t), 1, output);
	}
}
