/*
============================================================================
Name : 12.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Determine the opening mode of a file using the fcntl()
              system call.
Date: 7th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
    int fd;
    int flags;
    int mode;
    fd = open("/home/wither/Documents/os-labs/files/original.txt", O_RDWR);
    if(fd == -1){
        perror("open");
        return 1;
    }
    flags = fcntl(fd, F_GETFL);
    if(flags == -1){
        perror("fcntl");
        close(fd);
        return 1;
    }
    mode = flags & O_ACCMODE;
    if (mode == O_RDONLY)
        printf("File is opened in READ ONLY mode.\n");
    else if (mode == O_WRONLY)
        printf("File is opened in WRITE ONLY mode.\n");
    else if (mode == O_RDWR)
        printf("File is opened in READ-WRITE mode.\n");
    else
        printf("Unknown opening mode.\n");
    close(fd);
    return 0;
}