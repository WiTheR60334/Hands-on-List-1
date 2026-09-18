/*
============================================================================
Name : 23.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Create an orphan process by terminating the parent while
              the child process continues execution.
Date: 14th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        // Parent process
        printf("Parent PID = %d\n", getpid());
        printf("Child PID  = %d\n", pid);

        printf("Parent exiting...\n");
        exit(0);
    }
    else
    {
        // Child process
        printf("Child PID = %d\n", getpid());
        printf("Initial Parent PID = %d\n", getppid());

        // Give parent time to terminate
        sleep(5);

        printf("After parent exits:\n");
        printf("Child PID  = %d\n", getpid());
        printf("New Parent PID = %d\n", getppid());

        sleep(10);
    }

    return 0;
}