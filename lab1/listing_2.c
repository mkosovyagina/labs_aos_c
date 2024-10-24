#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define  FILE_OPEN_FAILED -1

int main(int argc, char *argv[]){
	int file_descriptor;
	int written_bytes;
	int read_bytes;
	int is_file_closed;	
	char message[] = "Hello, World!\nHave a nice day!!!\nWelcome to MEPHI! ;)";
	int message_len = sizeof(message);
	const char *file_name = argv[1]; 
	
	unsigned int access_mode = strtol(argv[2], NULL, 8);
	//unsigned int access_mode = strtol("0446", NULL, 8);
	
	file_descriptor = creat(file_name, access_mode);
	if (file_descriptor == FILE_OPEN_FAILED){
		perror("Failed to create file:");
		}
	else{
		printf("Creating new file %s\n", file_name);
		printf("Writing some text to file\n");
		written_bytes = write(file_descriptor, message, sizeof(message));
		if (written_bytes == FILE_OPEN_FAILED){
		perror("Failed to write content to file: ");
		return 1;}
		else{
			printf("Successfully written %d bytes\n", written_bytes);
			is_file_closed = close(file_descriptor);
			if(is_file_closed == FILE_OPEN_FAILED){
				perror("Failed to close file: ");
				return 1;}
			}
		
			if (is_file_closed == FILE_OPEN_FAILED){
				perror("Failed to close file: ");
				return 1;}	
		}
	file_descriptor = open(file_name, O_RDONLY);
	if (file_descriptor == FILE_OPEN_FAILED){
		perror("Failed to open file: ");
		return 1;}
	else{
		char read_buffer[message_len];
		read_bytes = read(file_descriptor, read_buffer, message_len);
		printf("%s\n", read_buffer);
		printf("Read bytes count: %d \n",read_bytes);
		close(file_descriptor);}
		
	file_descriptor = open(file_name, O_RDWR);
	perror("Try to open file with readonly access mode: ");			
	
	return 0;
}
