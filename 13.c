/*
============================================================================
Name : 13.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Wait for input from STDIN for 10 seconds using select()
              and verify whether data is available within the specified
              time.
Date: 7th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main(void){
    fd_set readfds;
    struct timeval timeout;
    char buffer[100];
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    printf("Waiting for input for 10 seconds...\n");
    fflush(stdout);
    int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
    if(ret == -1){
        perror("select");
        return 1;
    } else if (ret == 0) {
        printf("No input received within 10 seconds.\n");
    } else {
        if(FD_ISSET(STDIN_FILENO, &readfds)){
            printf("Input is available!\n");
            int n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
            if(n > 0){
                buffer[n] = '\0';
                printf("Input: %s", buffer);
            }
        }
    }
    return 0;
}