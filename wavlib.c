#include"wavlib.h"

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

