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
	char message[] = "MEPHI";
	int shift;
	int message_len = sizeof(message);
	const char *file_name = argv[1];
	//const char file_name[] = "testing_8.txt"; 
	
	unsigned int access_mode = strtol(argv[2], NULL, 8);
	
	file_descriptor = creat(file_name, access_mode);
	if (file_descriptor == FILE_OPEN_FAILED){
		perror("Failed to create file:");
		}
	else{
		for(int i=0; i < 5; i++){
			written_bytes = write(file_descriptor, message, message_len);
			shift = lseek(file_descriptor, i*80, SEEK_SET);
			if (written_bytes == FILE_OPEN_FAILED){
				perror("Failed to write content to file: ");
				return 1;
			}
		}
		}
	close(file_descriptor);			
	return 0;
}
