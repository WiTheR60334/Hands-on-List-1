/*
============================================================================
Name : 11.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Open a file, duplicate the file descriptor and append the
              file using both descriptors. Implement the operation using
              dup(), dup2() and fcntl().
Date: 4th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd, fd_dup, fd_dup2, fd_fcntl;
    fd = open("/home/wither/Documents/os-labs/files/q11.txt",
              O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644);
    if(fd == -1){
        perror("open");
        return 1;
    }
    fd_dup = dup(fd);
    if(fd_dup == -1){
        perror("dup");
        close(fd);
        return 1;
    }
    write(fd, "Using fd\n", 9);
    write(fd_dup, "Using dup\n", 10);
    printf("Original fd = %d\n", fd);
    printf("dup fd      = %d\n", fd_dup);
    close(fd_dup);
    fd_dup2 = dup2(fd, 10);
    if(fd_dup2 == -1){
        perror("dup2");
        close(fd);
        return 1;
    }
    write(fd, "Using fd again\n", 15);
    write(fd_dup2, "Using dup2\n", 11);
    printf("dup2 fd     = %d\n", fd_dup2);
    close(fd_dup2);
    fd_fcntl = fcntl(fd, F_DUPFD, 10);
    if(fd_fcntl == -1){
        perror("fcntl");
        close(fd);
        return 1;
    }
    write(fd, "Using fcntl original\n", 21);
    write(fd_fcntl, "Using fcntl duplicate\n", 22);
    printf("fcntl fd    = %d\n", fd_fcntl);
    close(fd_fcntl);
    close(fd);
    printf("Data appended successfully.\n");
    return 0;
}