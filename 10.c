/*
============================================================================
Name : 10.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Open a file in read-write mode, write 10 bytes, move the
              file pointer by 10 bytes using lseek() and write another
              10 bytes. Check the return value of lseek() and examine
              the empty spaces between the data using the od command.
Date: 4th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
    int fd;
    off_t ret;
    fd = open("/home/wither/Documents/os-labs/files/q10.txt",
              O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        perror("open");
        return 1;
    }
    if(write(fd, "ABCDEFGHIJ", 10) != 10){
        perror("write");
        close(fd);
        return 1;
    }
    printf("First 10 bytes written.\n");
    ret = lseek(fd, 10, SEEK_CUR);
    if(ret == (off_t)-1){
        perror("lseek");
        close(fd);
        return 1;
    }
    printf("Return value of lseek = %ld\n", (long)ret);
    if(write(fd, "1234567890", 10) != 10){
        perror("write");
        close(fd);
        return 1;
    }
    printf("Second 10 bytes written.\n");
    close(fd);
    return 0;
}