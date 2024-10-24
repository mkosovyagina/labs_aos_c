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
	const char *file_name = argv[1];
	int file_descriptor;
	int read_bytes;
	char buffer;
	int file_size;
	if(argc < 2) {
		printf("You need to enter filename");
		exit(1);}
	
	printf("Nothing works!!!!!!!!!!!!\n");	
	file_descriptor = open(file_name, O_RDONLY);
	printf("%d", file_descriptor);
	if (file_descriptor == FILE_OPEN_FAILED){
	   perror("Failed to open file: ");
	   exit(1);}
	file_size = lseek(file_descriptor, 0, SEEK_END);
	printf("%d", file_size);
	for(int i=file_size; i >= 0; i--){
		lseek(file_descriptor, i, SEEK_SET);
		read_bytes = read(file_descriptor, &buffer, 1);
		printf("%c", buffer);
		}		
	close(file_descriptor);
return 0;}
