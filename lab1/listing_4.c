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
	int position_cursor;
	char message[] = "Hello, World!\nHave a nice day!!!\nWelcome to MEPHI! ;)";
	char add_message[] = "one_two_three_four_five_six_sevebn_eight";
	int message_len = sizeof(message);
	const char *file_name = argv[1];
	//const char file_name[] = "testing.txt";
	char read_buffer_seek[5]; 
	
	unsigned int access_mode = strtol(argv[2], NULL, 8);
	
	file_descriptor = open(file_name, O_RDWR|O_CREAT, access_mode);
	if (file_descriptor == FILE_OPEN_FAILED){
		perror("Failed to create file:");
		}
	else{
		//use SEEK_END
		lseek(file_descriptor, -1, SEEK_END);
		written_bytes = write(file_descriptor, message, message_len);
		written_bytes = write(file_descriptor, add_message, sizeof(add_message));
		printf("Creating new file or reopening existing %s\n", file_name);
		printf("Writing some text to file\n");
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
			
		}
	file_descriptor = open(file_name, O_RDWR);	
	
	if (file_descriptor == FILE_OPEN_FAILED){
		perror("Failed to open file: ");
		return 1;}
	
	
	else{
		char read_buffer[message_len];
		lseek(file_descriptor, 0, SEEK_SET);
		read_bytes = read(file_descriptor, read_buffer, message_len);
		printf("First read bytes \n %s\n", read_buffer);
		printf("Read bytes count: %d \n",read_bytes);
		close(file_descriptor);
		}
	file_descriptor = open(file_name, O_RDWR);
		//USE SEEK_SET
		position_cursor = lseek(file_descriptor, 0, SEEK_SET);
		written_bytes = write(file_descriptor, "***********", 11);
		//use SEEK_CUR
		lseek(file_descriptor, 0, SEEK_CUR);
		read_bytes = read(file_descriptor, read_buffer_seek, sizeof(read_buffer_seek));
		printf("Read bytes from SEEK %s\n", read_buffer_seek);
		printf("Read bytes count: %d \n",read_bytes);
		//use SEEK_END
		lseek(file_descriptor, -10, SEEK_END);
		read_bytes = read(file_descriptor, read_buffer_seek, sizeof(read_buffer_seek));
		printf("Read bytes from SEEK from the end %s\n", read_buffer_seek);
		close(file_descriptor);	
		
	file_descriptor = open(file_name, O_RDWR);
	perror("Try to open file with readonly access mode: ");	
	close(file_descriptor);		
	
	return 0;
}
