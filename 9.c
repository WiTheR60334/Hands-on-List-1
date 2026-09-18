/*
============================================================================
Name : 9.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Print the inode, number of hard links, UID, GID, size,
              block size, number of blocks, last access time, last
              modification time and last change time of a given file.
Date: 3rd Sep, 2026.
============================================================================
*/

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]){
    struct stat st;
    if(argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    if(stat(argv[1], &st) == -1){
        perror("stat");
        return 1;
    }
    printf("Inode              : %lu\n", st.st_ino);
    printf("Hard Links         : %lu\n", st.st_nlink);
    printf("UID                : %u\n", st.st_uid);
    printf("GID                : %u\n", st.st_gid);
    printf("Size               : %ld bytes\n", st.st_size);
    printf("Block Size         : %ld bytes\n", st.st_blksize);
    printf("Number of Blocks   : %ld\n", st.st_blocks);

    printf("Last Access        : %s", ctime(&st.st_atime));
    printf("Last Modification  : %s", ctime(&st.st_mtime));
    printf("Last Change        : %s", ctime(&st.st_ctime));

    return 0;
}