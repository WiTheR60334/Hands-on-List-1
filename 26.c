/*
============================================================================
Name : 26.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Execute ls -Rl using execl(), execlp(), execle(),
              execv() and execvp() system calls.
Date: 16th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <1-5>\n", argv[0]);
        printf("1 -> execl\n");
        printf("2 -> execlp\n");
        printf("3 -> execle\n");
        printf("4 -> execv\n");
        printf("5 -> execvp\n");
        return 1;
    }

    int choice = atoi(argv[1]);

    switch (choice)
    {
        case 1:
        {
            printf("Using execl...\n");
            fflush(stdout);

            execl("/usr/bin/ls",
                  "ls",
                  "-Rl",
                  (char *)NULL);

            perror("execl");
            break;
        }

        case 2:
        {
            printf("Using execlp...\n");
            fflush(stdout);

            execlp("ls",
                   "ls",
                   "-Rl",
                   (char *)NULL);

            perror("execlp");
            break;
        }

        case 3:
        {
            printf("Using execle...\n");
            fflush(stdout);

            execle("/usr/bin/ls",
                   "ls",
                   "-Rl",
                   (char *)NULL,
                   environ);

            perror("execle");
            break;
        }

        case 4:
        {
            printf("Using execv...\n");
            fflush(stdout);

            char *args[] = {
                "ls",
                "-Rl",
                NULL
            };

            execv("/usr/bin/ls", args);

            perror("execv");
            break;
        }

        case 5:
        {
            printf("Using execvp...\n");
            fflush(stdout);

            char *args[] = {
                "ls",
                "-Rl",
                NULL
            };

            execvp("ls", args);

            perror("execvp");
            break;
        }

        default:
            printf("Invalid choice. Use 1-5.\n");
            return 1;
    }

    return 1;
}