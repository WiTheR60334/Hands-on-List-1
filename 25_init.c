/*
============================================================================
Name : 25_init.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Executable to be executed
Date: 15th Sep, 2026.
============================================================================
*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }

    printf("Hello, %s!\n", argv[1]);

    return 0;
}