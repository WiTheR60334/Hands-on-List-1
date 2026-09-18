/*
============================================================================
Name : 1.c
Author : Romir Bedekar
Description : Write a program to open an existing file in read-write mode.
              Experiment with the O_EXCL flag.
Date: 18th Sep, 2026.
============================================================================
*/

#include<stdio.h>
#include<unistd.h>

int main(){
    if(symlink("files/original.txt","files/symlink_sys")==-1){
        perror("symlink");
    } else {
        printf("Symbolic link created successfully.\n");
    }
    return 0;
}