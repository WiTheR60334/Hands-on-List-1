/*
============================================================================
Name : 15.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Display the environmental variables of the user using
              the environ variable.
Date: 8th Sep, 2026.
============================================================================
*/


#include <stdio.h>
extern char **environ;

int main(void){
    char **env = environ;
    while(*env != NULL){
        printf("%s\n", *env);
        env++;
    }
    return 0;
}