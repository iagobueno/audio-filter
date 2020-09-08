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

/*reads wav's file chunk*/
void readChunk(chunk *info){
		
}
