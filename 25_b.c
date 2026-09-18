/*
============================================================================
Name : 25_b.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Execute an executable program using an exec system call
              and pass input as a command-line argument.
Date: 15th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }

    printf("Executing hello...\n");

    execl("/home/wither/Documents/os-labs/bin/25_init",
          "hello",
          argv[1],
          (char *)NULL);

    perror("execl");

    return 1;
}