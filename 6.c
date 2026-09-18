/*
============================================================================
Name : 6.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Take input from STDIN and display it on STDOUT using only
              read() and write() system calls.
Date: 2nd Sep, 2026.
============================================================================
*/

#include <unistd.h>

int main(void){
    char buffer[100];
    int n;
    while ((n = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0){
        write(STDOUT_FILENO, buffer, n);
    }
    return 0;
}