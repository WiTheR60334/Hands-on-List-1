/*
============================================================================
Name : 5.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Create five new files in an infinite loop, execute the
              program in the background and inspect the file descriptor
              table at /proc/pid/fd.
Date: 1st Sep, 2026.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd[5];
    char filename[100];
    int count = 0;
    while(1){
        for(int i = 0; i < 5; i++){
            sprintf(filename, "/home/wither/Documents/os-labs/files/file_%d_%d.txt", count, i);
            fd[i] = open(filename, O_CREAT | O_RDWR, 0644);
            if (fd[i] == -1) {
                perror("open");
                return 1;
            }
        }
        printf("Created 5 files\n");
        count++;
        sleep(2);
    }
    return 0;
}