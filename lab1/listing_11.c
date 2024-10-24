#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define STD_IN 0
#define STD_OUT 1
#define FILE_OPEN_FAILED -1

int main(int argc, char *argv[]){
	int stat_res;	
	int i;
	int index_max_file;
	long current_file_size;
	long file_size_max = 0;
	struct stat file_stats;
	if(argc < 2) {
		printf("You need to enter filename");
		exit(1);}
	for(i=1;i<argc;i++){
		stat_res = stat(argv[i], &file_stats);
		if(stat_res != 0){
			printf("Unable to get stat for current file %s", argv[i]);}
		else{
		    current_file_size = (long)file_stats.st_size;
		    if (current_file_size > file_size_max){
		    	index_max_file = i;
		    	file_size_max = current_file_size;
		    	}	
		}
		}
	printf("The longest file is %s and its length is %ld bytes", argv[index_max_file], file_size_max);
return 0;}
