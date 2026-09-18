/*
============================================================================
Name : 2.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Develop a simple program to execute indefinitely in the
              background, traverse the /proc directory and extract
              relevant process information from the corresponding
              proc directories.
Date: 31st Aug, 2026.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>

int is_pid(const char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isdigit((unsigned char)name[i]))
            return 0;
    }
    return 1;
}

void show_file(const char *pid, const char *filename) {
    char path[256];
    char buffer[1024];

    snprintf(path, sizeof(path), "/proc/%s/%s", pid, filename);

    FILE *file = fopen(path, "r");
    if (file == NULL)
        return;

    printf("\n--- /proc/%s/%s ---\n", pid, filename);

    while (fgets(buffer, sizeof(buffer), file) != NULL)
        printf("%s", buffer);

    fclose(file);
}

int main(void) {
    while (1) {
        DIR *proc = opendir("/proc");

        if (proc == NULL) {
            perror("opendir /proc");
            return 1;
        }

        struct dirent *entry;

        while ((entry = readdir(proc)) != NULL) {

            /* Process directories have numeric names */
            if (!is_pid(entry->d_name))
                continue;

            printf("\n====================================\n");
            printf("PID: %s\n", entry->d_name);
            printf("====================================\n");

            show_file(entry->d_name, "comm");
            show_file(entry->d_name, "status");
            show_file(entry->d_name, "stat");
            show_file(entry->d_name, "statm");
            show_file(entry->d_name, "cmdline");
        }

        closedir(proc);

        /* Wait 5 seconds before scanning again */
        sleep(5);
    }

    return 0;
}