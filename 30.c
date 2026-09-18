/*
============================================================================
Name : 30.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Create a daemon process that executes a task or script
              at a specified time.
Date: 18th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

#define LOG_FILE "/home/wither/Documents/os-labs/files/q30-daemon.log"

void daemonize(void)
{
    pid_t pid;

    // First fork
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid > 0)
    {
        // Parent exits
        exit(0);
    }

    // Create new session
    if (setsid() == -1)
    {
        perror("setsid");
        exit(1);
    }

    // Second fork
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid > 0)
    {
        // First child exits
        exit(0);
    }

    // Change working directory
    chdir("/");

    // Clear file creation mask
    umask(0);

    // Redirect standard input/output/error to /dev/null
    int devnull = open("/dev/null", O_RDWR);

    if (devnull == -1)
    {
        exit(1);
    }

    dup2(devnull, STDIN_FILENO);
    dup2(devnull, STDOUT_FILENO);
    dup2(devnull, STDERR_FILENO);

    if (devnull > STDERR_FILENO)
        close(devnull);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <HH:MM> <script-path>\n", argv[0]);
        printf("Example: %s 18:30 /home/wither/Documents/os-labs/files/task.sh\n",
               argv[0]);
        return 1;
    }

    int hour, minute;

    if (sscanf(argv[1], "%d:%d", &hour, &minute) != 2 ||
        hour < 0 || hour > 23 ||
        minute < 0 || minute > 59)
    {
        printf("Invalid time. Use HH:MM format.\n");
        return 1;
    }

    daemonize();

    /*
     * Open daemon log file
     */
    int logfd = open(LOG_FILE,
                     O_WRONLY | O_CREAT | O_APPEND,
                     0644);

    if (logfd == -1)
        exit(1);

    time_t now;
    struct tm target;

    time(&now);

    target = *localtime(&now);

    target.tm_hour = hour;
    target.tm_min = minute;
    target.tm_sec = 0;

    time_t target_time = mktime(&target);

    /*
     * If the specified time has already passed today,
     * schedule it for tomorrow.
     */
    if (target_time <= now)
    {
        target.tm_mday++;
        target_time = mktime(&target);
    }

    /*
     * Calculate how many seconds to wait.
     */
    unsigned long wait_seconds =
        (unsigned long)difftime(target_time, now);

    dprintf(logfd,
            "Daemon started. PID = %d\n",
            getpid());

    dprintf(logfd,
            "Waiting until %02d:%02d\n",
            hour, minute);

    /*
     * Wait until target time
     */
    while (wait_seconds > 0)
    {
        unsigned int slept = sleep(wait_seconds);
        wait_seconds = slept;
    }

    dprintf(logfd,
            "Executing script at %02d:%02d\n",
            hour, minute);

    /*
     * Execute the shell script
     */
    execl("/bin/sh",
          "sh",
          argv[2],
          (char *)NULL);

    /*
     * Reached only if execl() fails
     */
    dprintf(logfd,
            "execl failed\n");

    close(logfd);

    return 1;
}