#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *list = NULL;

struct node *curList = NULL;

int curPriority = MAX_PRIORITY;

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
    if (curList == NULL)
        return NULL;

    Task *selected = curList->task;
    delete (&curList, selected);

    return selected;
}

void orderedList()
{

    struct node *p = list;

    int priority = curPriority;

    while (p != NULL)
    {

        if (p->task->priority == priority)
        {

            insert(&curList, p->task);
        }

        p = p->next;
    }
}

void schedule()
{

    double totalWaitingTime = 0, totalTurnaroundTime = 0, totalResponseTime = 0;
    int count = 0;
    int currentTime = 0;

    while (curPriority != 0)
    {
        orderedList();

        Task *task;

        while ((task = pickNextTask()) != NULL)
        {

            if (task->burst > 0)
            {

                if (task->tid == 0)
                {
                    totalResponseTime += currentTime;
                    task->tid = task->burst;
                }

                if (curList == NULL)
                {
                    run(task, task->burst);
                    currentTime += task->burst;
                    task->burst = 0;
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

                if (task->burst > 0)
                {
                    run(task, timeSlice);
                    currentTime += timeSlice;
                    task->burst -= timeSlice;
                }

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
                    insert(&curList, task);
                }
            }
        }

        curList = NULL;
        curPriority--;
    }

    printf("\nAverage Waiting time = %.2f \n", totalWaitingTime / count);
    printf("Average Turnaround time = %.2f \n", totalTurnaroundTime / count);
    printf("Average Response time = %.2f \n", totalResponseTime / count);
}
