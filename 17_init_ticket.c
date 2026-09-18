/*
============================================================================
Name : 17_init_ticket.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Open a file, store an initial ticket number and exit.
Date: 9th Sep, 2026.
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    int ticket = 100;

    fd = open("/home/wither/Documents/os-labs/files/ticket.txt",
              O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    if (write(fd, &ticket, sizeof(ticket)) != sizeof(ticket))
    {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Initial ticket number stored: %d\n", ticket);

    close(fd);

    return 0;
}