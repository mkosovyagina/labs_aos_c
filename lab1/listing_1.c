/*
1. Написать программу, которая выполняет некоторый системный вызов, 
например open, и затем выводит возвращаемую ошибку. 

Использовать в программе разные способы вывода сообщения об ошибке: 
    вывод значения errno, 
    вывод соответствующего сообщения из системного массива сообщений об ошибках sys_errlist[], 
    вызов библиотечной функции perror.
*/

#include <stdio.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <unistd.h>

#define PATH "some_nonexistent_file.txt"
#define FILE_OPEN_FAILED -1

int main() {

    int file_descriptor = open(PATH, O_RDWR);

    if (file_descriptor == FILE_OPEN_FAILED) {
        printf("errno_code: %d\n", errno);
        perror("perror");
        printf("sys_errlist: %s\n", sys_errlist[errno]);
        change_printf_to_log();
    }
    return 0;
}
