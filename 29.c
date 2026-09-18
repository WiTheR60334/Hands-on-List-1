/*
============================================================================
Name : 29.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Obtain the scheduling policy of a process and modify it
              using policies such as SCHED_FIFO and SCHED_RR.
Date: 17th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

void print_policy(int policy)
{
    switch (policy)
    {
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;

        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;

        case SCHED_RR:
            printf("SCHED_RR\n");
            break;

        default:
            printf("Unknown policy\n");
    }
}

int main(int argc, char *argv[])
{
    int policy;
    struct sched_param param;

    if (argc != 2)
    {
        printf("Usage: %s <1|2>\n", argv[0]);
        printf("1 -> SCHED_FIFO\n");
        printf("2 -> SCHED_RR\n");
        return 1;
    }

    /*
     * Get current scheduling policy
     */
    policy = sched_getscheduler(0);

    if (policy == -1)
    {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Current scheduling policy: ");
    print_policy(policy);

    /*
     * Choose new policy
     */
    if (atoi(argv[1]) == 1)
        policy = SCHED_FIFO;
    else if (atoi(argv[1]) == 2)
        policy = SCHED_RR;
    else
    {
        printf("Invalid choice.\n");
        return 1;
    }

    /*
     * Set a valid real-time priority
     */
    param.sched_priority = sched_get_priority_min(policy);

    /*
     * Modify scheduling policy
     */
    if (sched_setscheduler(0, policy, &param) == -1)
    {
        perror("sched_setscheduler");
        return 1;
    }

    printf("New scheduling policy: ");
    print_policy(sched_getscheduler(0));

    printf("Priority: %d\n", param.sched_priority);

    return 0;
}