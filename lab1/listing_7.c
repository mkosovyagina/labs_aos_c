#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]){
	int file_descriptor;
	struct stat file_stats;
	const char *file_name = argv[1];
	struct stat file_stat;
	mode_t mode;
	
	stat(file_name, &file_stat);
	mode = file_stat.st_mode & S_IFMT;
	printf("%o\n", mode);
	
	if(mode == S_IFDIR)
		printf("It's a directory\n");
	else printf("\n");	
	if(mode == S_IFREG){
		printf("It's a common file\n");
		printf("inode: %ld\n",file_stat.st_ino);
		printf("Device ID with file: %ld\n",file_stat.st_dev);}
	else printf("\n");	
	if(file_stat.st_mode & S_IFMT == S_IFBLK){
		printf("It's a special file\n");
		printf("device number adress: %ld\n", file_stat.st_rdev);
		}
	else printf("\n");
	printf("File permissions: %o\n",file_stat.st_mode & S_IFMT);
	printf("Number of hard links:%ld\n",file_stat.st_nlink);
	printf("File size in bytes: %ld\n", file_stat.st_size);
	printf("File size in blocks: %ld\n", file_stat.st_blocks);
	printf("User ID:%d\n",file_stat.st_uid);
	printf("Group ID:%d\n",file_stat.st_gid);
	printf("Last access time:\t\t\t%s",asctime(localtime(&file_stat.st_atime)));
	printf("Last content modification time:\t\t%s",asctime(localtime(&file_stat.st_mtime)));
	printf("Last attributes modification time:\t%s",asctime(localtime(&file_stat.st_ctime)));	
		
	return 0;
}
