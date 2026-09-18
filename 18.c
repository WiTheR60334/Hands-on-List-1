/*
============================================================================
Name : 18.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Perform record locking with read and write locks. Create
              three records in a file and lock the required record before
              accessing or modifying it to avoid race conditions.
Date: 10th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FILE_NAME "/home/wither/Documents/os-labs/files/records.dat"

typedef struct
{
    int id;
    char name[50];
} Record;

/*
 * Create 3 records if the file is empty/new.
 */
void create_records(int fd)
{
    struct stat st;

    if (fstat(fd, &st) == -1)
    {
        perror("fstat");
        exit(1);
    }

    if (st.st_size == 0)
    {
        Record records[3] =
        {
            {1, "Alice"},
            {2, "Bob"},
            {3, "Charlie"}
        };

        if (write(fd, records, sizeof(records)) != sizeof(records))
        {
            perror("write");
            exit(1);
        }

        printf("3 records created.\n");
    }
}

/*
 * Lock one particular record.
 *
 * record_no = 1, 2 or 3
 * type      = F_RDLCK or F_WRLCK
 */
void lock_record(int fd, int record_no, short type)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_whence = SEEK_SET;
    lock.l_start = (record_no - 1) * sizeof(Record);
    lock.l_len = sizeof(Record);
    lock.l_pid = getpid();

    if (fcntl(fd, F_SETLKW, &lock) == -1)
    {
        perror("fcntl lock");
        exit(1);
    }

    if (type == F_WRLCK)
        printf("WRITE lock acquired on record %d\n", record_no);
    else
        printf("READ lock acquired on record %d\n", record_no);
}

/*
 * Unlock one particular record.
 */
void unlock_record(int fd, int record_no)
{
    struct flock lock;

    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = (record_no - 1) * sizeof(Record);
    lock.l_len = sizeof(Record);
    lock.l_pid = getpid();

    if (fcntl(fd, F_SETLK, &lock) == -1)
    {
        perror("fcntl unlock");
        exit(1);
    }

    printf("Record %d unlocked.\n", record_no);
}

int main(int argc, char *argv[])
{
    int fd;
    int record_no;
    char mode;
    Record record;

    if (argc != 3)
    {
        printf("Usage:\n");
        printf("  %s r <record_number>\n", argv[0]);
        printf("  %s w <record_number>\n", argv[0]);
        return 1;
    }

    mode = argv[1][0];
    record_no = atoi(argv[2]);

    if ((mode != 'r' && mode != 'w') ||
        record_no < 1 || record_no > 3)
    {
        printf("Invalid input.\n");
        printf("Record number must be 1, 2 or 3.\n");
        return 1;
    }

    fd = open(FILE_NAME, O_RDWR | O_CREAT, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    create_records(fd);

    /*
     * ------------------------------------------------
     * WRITE LOCK
     * ------------------------------------------------
     */
    if (mode == 'w')
    {
        lock_record(fd, record_no, F_WRLCK);

        /*
         * Move to the selected record.
         */
        if (lseek(fd,
                  (record_no - 1) * sizeof(Record),
                  SEEK_SET) == (off_t)-1)
        {
            perror("lseek");
            close(fd);
            return 1;
        }

        /*
         * Read the selected record.
         */
        if (read(fd, &record, sizeof(Record)) != sizeof(Record))
        {
            perror("read");
            close(fd);
            return 1;
        }

        printf("Before modification:\n");
        printf("ID   : %d\n", record.id);
        printf("Name : %s\n", record.name);

        /*
         * Example modification.
         */
        record.id++;

        /*
         * Move back to beginning of the same record.
         */
        if (lseek(fd,
                  (record_no - 1) * sizeof(Record),
                  SEEK_SET) == (off_t)-1)
        {
            perror("lseek");
            close(fd);
            return 1;
        }

        /*
         * Write modified record.
         */
        if (write(fd, &record, sizeof(Record)) != sizeof(Record))
        {
            perror("write");
            close(fd);
            return 1;
        }

        printf("After modification:\n");
        printf("ID   : %d\n", record.id);
        printf("Name : %s\n", record.name);

        unlock_record(fd, record_no);
    }

    /*
     * ------------------------------------------------
     * READ LOCK
     * ------------------------------------------------
     */
    else
    {
        lock_record(fd, record_no, F_RDLCK);

        /*
         * Move to selected record.
         */
        if (lseek(fd,
                  (record_no - 1) * sizeof(Record),
                  SEEK_SET) == (off_t)-1)
        {
            perror("lseek");
            close(fd);
            return 1;
        }

        /*
         * Read selected record.
         */
        if (read(fd, &record, sizeof(Record)) != sizeof(Record))
        {
            perror("read");
            close(fd);
            return 1;
        }

        printf("Record %d:\n", record_no);
        printf("ID   : %d\n", record.id);
        printf("Name : %s\n", record.name);

        unlock_record(fd, record_no);
    }

    close(fd);

    return 0;
}