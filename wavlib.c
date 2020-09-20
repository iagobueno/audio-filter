/*GRR20190171 Carlos Iago Bueno*/
#include"wavlib.h"
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

/*checks if a file was opened correclty*/
void checksFile(FILE *file){
        if(!file){
                perror("file wasn't opened correctly");
                exit(1);
        }
}

/*deals the used flags*/
void flags(char **input_flag, char **output_flag, double *level, double *delay, int argc, char **argv){
	int flag;
	opterr=0;

	for(;(flag=getopt(argc,argv,"i:o:l:t:")) != -1;){
		if(flag =='i')
			*input_flag=optarg;
		if(flag =='o')
			*output_flag=optarg;
		if(flag =='l')
			*level=atof(optarg);
		if(flag =='t')
			*delay=atof(optarg);
		
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
	fread(info, sizeof(chunk_t), 1, file);
}

/*copy the input's chunk to the output's chunk*/
void copyChunk(FILE *input, FILE *output){
	chunk_t info;
	rewind(input);
	fread(&info, sizeof(chunk_t), 1, input);
	fwrite(&info, sizeof(chunk_t), 1, output);
}

/*checks if level is a acceptable value*/
double checksLevel(double level, double standart, double lower, double higher){
	if(!level || level < lower)
		return standart;
	if(level > higher)	
		return higher;
	return level;
}

/*checks if a sample has passed the wave limit and ajust it*/
int16_t checksSample(double sample){

	if(sample > 0){
		if( sample > MAX)
			return MAX;
	}
	else{
		if( sample < MIN)
			return MIN;
	}

	return sample;
}

/*finds the greatest value into a array*/
int16_t findGreatest(int16_t *array, int size){
	int i;
	int16_t great, aux;

	for(i=0, great=0;i<size;i++){
		if(array[i] < 0)
			aux = array[i] * (-1);
		else
			aux = array[i];
		if(aux > great)
			great=array[i];
	}

	return great;
}

/*open n files*/
FILE **openFiles(int n, char **argv){

	FILE **files = malloc( n * sizeof(FILE*));

	int i, j;
	for(i=0, j=1;i<n;i++, j++){

		/*ignore the files that cames from the -o flag*/
		if(!strcmp(argv[j],"-o"))
			j+=2;

		files[i] = fopen(argv[j],"r");
		checksFile(files[i]);
	}
	
	return files;
}

/*returns the numbers of files, disregarding the files that cames from flags*/
int numbersOfFiles(FILE *output, int argc){
	if(output == stdout)
		return argc-1;
	return argc-3;
}

