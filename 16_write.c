/*
============================================================================
Name : 16_write.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Perform mandatory locking and implement a write lock
              using fcntl().
Date: 9th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
    int fd;
    struct flock lock;
    fd = open("/home/wither/Documents/os-labs/files/q16.txt",
              O_RDWR | O_CREAT, 0644);
    if(fd == -1){
        perror("open");
        return 1;
    }
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;       // Lock entire file
    lock.l_pid = getpid();
    printf("Trying to acquire WRITE lock...\n");
    if(fcntl(fd, F_SETLKW, &lock) == -1){
        perror("fcntl");
        close(fd);
        return 1;
    }
    printf("WRITE lock acquired.\n");
    printf("PID = %d\n", getpid());
    printf("File is locked. Press Enter to release the lock...\n");
    getchar();
    lock.l_type = F_UNLCK;
    if(fcntl(fd, F_SETLK, &lock) == -1){
        perror("unlock");
    } else {
        printf("WRITE lock released.\n");
    }
    close(fd);
    return 0;
}