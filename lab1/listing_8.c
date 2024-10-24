#include <sys/stat.h>
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

void copy_file(int file_descriptor_source, int file_descriptor_destination){
    char one_byte[1];

    while((read(file_descriptor_source, one_byte, sizeof(one_byte))) > 0){
	write(file_descriptor_destination, one_byte, sizeof(one_byte));
    }
    printf("Copy completed\n");        
}

int main(int argc, char *argv[]){	
	const char *file_name_source = argv[1];
	const char *file_name_destination = argv[2];
	int file_descriptor_source;
	int file_descriptor_destination;
	
	if (argc < 3){	
	    file_descriptor_source = STD_IN;
	    file_descriptor_destination = STD_OUT;
	    printf("Using STD_IN and STD_OUT\n");
	    printf("Put some text\n");
	    }
	else{
	    file_descriptor_source = open(file_name_source, O_RDONLY);
	    if (file_descriptor_source == FILE_OPEN_FAILED){
	    	perror("Failed to open file: ");
	    	exit(1);}
	    
	    file_descriptor_destination	= creat(file_name_destination, 0755);
	    if (file_descriptor_source == FILE_OPEN_FAILED){
	    	perror("Failed to open file: ");
	    	exit(1);}
		}   
	copy_file(file_descriptor_source, file_descriptor_destination);

    	close(file_descriptor_source);
    	close(file_descriptor_destination);   	 
		
	return 0;
}
