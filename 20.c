/*
============================================================================
Name : 20.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Create a child process using fork() and print both the
              parent and child process IDs.
Date: 11th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        printf("Child Process:\n");
        printf("Child PID  = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());
    }
    else
    {
        // Parent process
        printf("Parent Process:\n");
        printf("Parent PID = %d\n", getpid());
        printf("Child PID  = %d\n", pid);
    }

    return 0;
}