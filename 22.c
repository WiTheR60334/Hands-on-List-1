/*
============================================================================
Name : 22.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Create a zombie process by allowing the child process to
              terminate while the parent remains alive without calling
              wait().
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

    if (pid == 0)
    {
        // Child process
        printf("Child: PID = %d\n", getpid());
        printf("Child exiting...\n");

        exit(0);
    }
    else
    {
        // Parent process
        printf("Parent: PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);

        printf("Parent sleeping for 30 seconds...\n");

        // Parent does NOT call wait()
        sleep(30);
    }

    return 0;
}