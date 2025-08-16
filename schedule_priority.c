#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *list = NULL;

int curPriority = MAX_PRIORITY;

void add(char *name, int priority, int burst)
{

    Task *task = malloc(sizeof(Task));

    task->name = name;
    task->priority = priority;
    task->burst = burst;

    insert(&list, task);
}

void swapTask(struct node *p1, struct node *p2)
{
    Task *temp = p1->task;
    p1->task = p2->task;
    p2->task = temp;
}

Task *pickNextTask()
{
    if (list == NULL)
        return NULL;

    Task *selected = list->task;
    delete (&list, selected);

    return selected;
}

void orderedList()
{

    struct node *list2 = NULL;
    struct node *p = list;

    while (curPriority != 0)
    {
        p = list;

        while (p != NULL)
        {

            if (p->task->priority == curPriority)
            {

                insert(&list2, p->task);
            }

            p = p->next;
        }

        curPriority--;
    }

    list = list2;
}

void schedule()
{

    double prevBursts, burstTotal = 0, count = 0, total = 0;

    orderedList();

    Task *task;

    while ((task = pickNextTask()) != NULL)
    {

        if (count > 0)
        {

            total += prevBursts;
        }

        prevBursts += task->burst;
        burstTotal += prevBursts;

        count++;

        run(task, task->burst);
        free(task->name); 
        free(task);
    }

    printf("\nAverage Waiting time = %.2f \n", (total / count));
    printf("Average turnAround time = %.2f \n", (burstTotal / count));
    printf("Average response time = %.2f \n", (total / count));
}
