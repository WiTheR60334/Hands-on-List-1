/*
============================================================================
Name : 24.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Create three child processes and make the parent wait for
              a specific child using the waitpid() system call.
Date: 15th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    pid_t child[3];
    int status;

    // Create 3 child processes
    for (int i = 0; i < 3; i++)
    {
        child[i] = fork();

        if (child[i] < 0)
        {
            perror("fork");
            return 1;
        }

        if (child[i] == 0)
        {
            printf("Child %d: PID = %d, Parent PID = %d\n",
                   i + 1, getpid(), getppid());

            // Make children finish at different times
            sleep((i + 1) * 2);

            printf("Child %d exiting...\n", i + 1);
            exit(10 + i);
        }
    }

    // Parent process
    printf("\nParent PID = %d\n", getpid());

    printf("Created children:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("Child %d PID = %d\n", i + 1, child[i]);
    }

    /*
     * Wait specifically for Child 2
     */
    printf("\nParent waiting for Child 2 (PID = %d)...\n", child[1]);

    if (waitpid(child[1], &status, 0) == -1)
    {
        perror("waitpid");
        return 1;
    }

    if (WIFEXITED(status))
    {
        printf("Child 2 terminated with exit status = %d\n",
               WEXITSTATUS(status));
    }

    /*
     * Reap the remaining children
     */
    waitpid(child[0], NULL, 0);
    waitpid(child[2], NULL, 0);

    printf("Parent exiting.\n");

    return 0;
}