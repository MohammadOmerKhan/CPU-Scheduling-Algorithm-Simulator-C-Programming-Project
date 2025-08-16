#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *list = NULL;

void add(char *name, int priority, int burst)
{

    Task *task = malloc(sizeof(Task));

    task->name = name;
    task->priority = priority;
    task->burst = burst;
    task->tid = 0;

    insert(&list, task);
}

Task *pickNextTask()
{
    if (list == NULL)
        return NULL;

    Task *selected = list->task;
    delete (&list, selected);

    return selected;
}

void schedule()
{
    Task *task;
    double totalWaitingTime = 0, totalTurnaroundTime = 0, totalResponseTime = 0;
    int count = 0;
    int currentTime = 0;

    while ((task = pickNextTask()) != NULL)
    {
        if (task->tid == 0)
        {
            task->tid = task->burst;
            totalResponseTime += currentTime;
        }

        int timeSlice;
        if (task->burst > 10)
        {
            timeSlice = 10;
        }
        else
        {
            timeSlice = task->burst;
        }
        run(task, timeSlice);
        currentTime += timeSlice;
        task->burst -= timeSlice;

        if (task->burst == 0)
        {
            int turnaroundTime = currentTime;
            int waitingTime = turnaroundTime - task->tid;

            totalWaitingTime += waitingTime;
            totalTurnaroundTime += turnaroundTime;
            count++;
        }
        else
        {
            insert(&list, task);
        }
    }

    printf("\nAverage Waiting time = %.2f \n", totalWaitingTime / count);
    printf("Average Turnaround time = %.2f \n", totalTurnaroundTime / count);
    printf("Average Response time = %.2f \n", totalResponseTime / count);
}
