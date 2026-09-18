/*
============================================================================
Name : 28.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Find the priority of a running program and modify its
              niceness using the nice/renice command.
Date: 17th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("PID = %d\n", getpid());
    printf("Program is running...\n");

    while (1)
    {
        sleep(1);
    }

    return 0;
}