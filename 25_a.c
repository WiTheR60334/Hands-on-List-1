/*
============================================================================
Name : 25_a.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Execute another executable program using an exec system
              call.
Date: 15th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Before exec()\n");

    execl("/home/wither/Documents/os-labs/bin/25_init",
          "hello",
          "Wither",
          (char *)NULL);

    perror("execl");

    return 1;
}