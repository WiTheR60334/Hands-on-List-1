/*
============================================================================
Name : 21.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Open a file, call fork() and allow both the parent and
              child processes to write to the file. Examine the output
              of the file.
Date: 11th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    pid_t pid;

    fd = open("/home/wither/Documents/os-labs/files/q21.txt",
              O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        close(fd);
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        write(fd, "Hello from Child\n", 17);
        printf("Child: PID = %d\n", getpid());
    }
    else
    {
        // Parent process
        write(fd, "Hello from Parent\n", 18);
        printf("Parent: PID = %d, Child PID = %d\n",
               getpid(), pid);
    }

    close(fd);

    return 0;
}