/*
============================================================================
Name : 17.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Open the ticket file, implement a write lock, read the
              ticket number, increment it, print the new ticket number
              and close the file.
Date: 9th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    int ticket;
    struct flock lock;

    fd = open("/home/wither/Documents/os-labs/files/ticket.txt",
              O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    /*
     * Create a write lock on the entire file
     */
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    printf("Process %d: Trying to acquire write lock...\n", getpid());

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl");
        close(fd);
        return 1;
    }

    printf("Process %d: Write lock acquired.\n", getpid());

    /*
     * Read current ticket number
     */
    if (read(fd, &ticket, sizeof(ticket)) != sizeof(ticket))
    {
        perror("read");
        close(fd);
        return 1;
    }

    /*
     * Increment ticket number
     */
    ticket++;

    /*
     * Move file pointer back to beginning
     */
    if (lseek(fd, 0, SEEK_SET) == (off_t)-1)
    {
        perror("lseek");
        close(fd);
        return 1;
    }

    /*
     * Store updated ticket number
     */
    if (write(fd, &ticket, sizeof(ticket)) != sizeof(ticket))
    {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Process %d: New ticket number = %d\n", getpid(), ticket);

    /*
     * Release lock
     */
    lock.l_type = F_UNLCK;

    if (fcntl(fd, F_SETLK, &lock) == -1)
    {
        perror("unlock");
    }
    close(fd);
    return 0;
}