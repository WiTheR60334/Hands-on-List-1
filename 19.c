/*
============================================================================
Name : 19.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Create a process in running, sleeping and stopped states
              and verify the current state using relevant commands.
Date: 10th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <running|sleeping|stopped>\n", argv[0]);
        return 1;
    }

    printf("PID = %d\n", getpid());
    fflush(stdout);

    if (strcmp(argv[1], "running") == 0)
    {
        printf("Process is now running...\n");
        fflush(stdout);

        while (1)
        {
        }
    }
    else if (strcmp(argv[1], "sleeping") == 0)
    {
        printf("Process is now sleeping...\n");
        fflush(stdout);

        while (1)
        {
            sleep(5);
        }
    }
    else if (strcmp(argv[1], "stopped") == 0)
    {
        printf("Process will now stop...\n");
        fflush(stdout);

        raise(SIGSTOP);

        printf("Process resumed.\n");
    }
    else
    {
        printf("Invalid state.\n");
        return 1;
    }

    return 0;
}