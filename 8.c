/*
============================================================================
Name : 8.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Open a file in read-only mode, read the file line by line,
              display each line as it is read and close the file when
              the end of the file is reached.
Date: 3rd Sep, 2026.
============================================================================
*/

#include <stdio.h>

int main(void){
    FILE *file;
    char line[1024];
    file = fopen("/home/wither/Documents/os-labs/files/original.txt", "r");
    if(file == NULL){
        perror("fopen");
        return 1;
    }
    while(fgets(line, sizeof(line), file) != NULL){
        printf("%s", line);
    }
    fclose(file);
    return 0;
}