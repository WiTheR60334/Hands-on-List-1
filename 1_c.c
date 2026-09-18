/*
============================================================================
Name : 1_c.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Create a FIFO using the mkfifo library function.
Date: 28th Aug, 2026.
============================================================================
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
    const char *fifo = "/home/wither/Documents/os-labs/files/myfifo";

    if (mkfifo(fifo, 0666) == -1)
    {
        if (errno == EEXIST)
            printf("FIFO already exists.\n");
        else
        {
            perror("mkfifo");
            return 1;
        }
    }

    printf("FIFO created successfully.\n");
    printf("FIFO path: %s\n", fifo);

    return 0;
}


// Output : 
// ╭─[~/Documents/os-labs]─[wither@obsidian]─[0]─[1837]
// ╰─[:)] % ~/Documents/os-labs/bin/1_c  
// FIFO created successfully.
// FIFO path: /home/wither/Documents/os-labs/files/myfifo