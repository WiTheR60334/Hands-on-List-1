/*
============================================================================
Name : 3.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Create a file and print its file descriptor value using
              the creat() system call.
Date: 31st Aug, 2026.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    fd = creat("/home/wither/Documents/os-labs/files/example.txt", 0644);
    if (fd == -1) {
        perror("creat");
        return 1;
    }
    printf("File created successfully.\n");
    printf("File descriptor = %d\n", fd);
    close(fd);
    return 0;
}