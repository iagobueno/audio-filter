#include"wavlib.h"

/*checks if a file was opened correclty*/
void checksFile(FILE *file){
        if(!file){
                perror("file wasn't opened correctly");
                exit(1);
        }
}

/*deals the used flags*/
void ioFlags(char **input_flag, char **output_flag, int argc, char **argv){
	int flag;
	opterr=0;

	for(;(flag=getopt(argc,argv,"i:o:")) != -1;){
		if(flag =='i'){
			*input_flag=optarg;
		}
		if(flag =='o'){
			*output_flag=optarg;
		}
	}
	
}

/*checks if the input comes from stdin or by flag*/
FILE *checksInput(char *input_flag){
	FILE *file=NULL;
	if(input_flag)
		file = fopen(input_flag, "r");
	else
                file = stdin;

	checksFile(file);

	return file;
}

/*reads wav's file chunk*/
void readChunk(chunk *info, FILE *file){
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

	info->bytesps=(uint32_t)info->bitsps/8;
}

void printChunk(chunk *info){
	printf("riff tag	(4 bytes): %s\n", info->id);
	printf("riff size	(4 bytes): %u\n", info->size);
	printf("wave tag	(4 bytes): %s\n", info->format);
	printf("form tag	(4 bytes): %s\n", info->sub1id);
	printf("fmt_size	(4 bytes): %u\n", info->sub1size);
	printf("audio_format	(2 bytes): %u\n", info->audioformat);
	printf("num_channels	(2 bytes): %u\n", info->nchannels);
	printf("sample_rate	(4 bytes): %u\n", info->samplerate);
	printf("byte_rate	(4 bytes): %u\n", info->byterate);
	printf("block_align	(2 bytes): %u\n", info->blockalign);
	printf("bits_per_sample	(2 bytes): %u\n", info->bitsps);
	printf("data tag	(4 bytes): %s\n", info->sub2id);
	printf("data size	(4 bytes): %u\n", info->sub2size);
	printf("bytes per sample	 : %u\n", info->bytesps);
}
