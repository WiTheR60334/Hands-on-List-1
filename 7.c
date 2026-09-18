/*
============================================================================
Name : 7.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Copy the contents of file1 into file2, emulating the
              cp file1 file2 command.
Date: 2nd Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int src, dest;
    char buffer[1024];
    ssize_t bytesRead, bytesWritten;
    if(argc != 3){
        printf("Usage: %s file1 file2\n", argv[0]);
        return 1;
    }
    src = open(argv[1], O_RDONLY);
    if(src == -1){
        perror("open source");
        return 1;
    }
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(dest == -1){
        perror("open destination");
        close(src);
        return 1;
    }
    while((bytesRead = read(src, buffer, sizeof(buffer))) > 0){
        bytesWritten = write(dest, buffer, bytesRead);
        if(bytesWritten == -1){
            perror("write");
            close(src);
            close(dest);
            return 1;
        }
    }
    if(bytesRead == -1){
        perror("read");
    }
    close(src);
    close(dest);
    return 0;
}