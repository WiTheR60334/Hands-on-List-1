/*
============================================================================
Name : 27.c
Author : Romir Bedekar
Roll No : MT2026082
Description : Retrieve the maximum and minimum real-time scheduling
              priority.
Date: 16th Sep, 2026.
============================================================================
*/


#include <stdio.h>
#include <sched.h>

int main(void)
{
    int max_priority;
    int min_priority;

    max_priority = sched_get_priority_max(SCHED_FIFO);
    min_priority = sched_get_priority_min(SCHED_FIFO);

    if (max_priority == -1 || min_priority == -1)
    {
        perror("sched_get_priority");
        return 1;
    }

    printf("Scheduling Policy : SCHED_FIFO\n");
    printf("Maximum RT Priority: %d\n", max_priority);
    printf("Minimum RT Priority: %d\n", min_priority);

    return 0;
}