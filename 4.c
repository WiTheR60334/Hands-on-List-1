/*
============================================================================
Name : 4.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Open an existing file in read-write mode and experiment
              with the O_EXCL flag.
Date: 1st Sep, 2026.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd;
    fd = open("/home/wither/Documents/os-labs/files/example.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        return 1;
    }
    printf("File opened successfully.\n");
    printf("File descriptor = %d\n", fd);
    close(fd);
    fd = open("/home/wither/Documents/os-labs/files/example.txt",
              O_CREAT | O_EXCL | O_RDWR, 0644);
    if (fd == -1) {
        perror("O_EXCL open");
    } else {
        printf("File created successfully with O_EXCL.\n");
        close(fd);
    }
    return 0;
}