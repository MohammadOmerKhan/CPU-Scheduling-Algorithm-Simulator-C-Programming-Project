#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

    double prevBursts, burstTotal = 0, count = 0, total = 0;


    Task *task;

    while ((task = pickNextTask()) != NULL)
    { 

    

    if(count>0){

        total+= prevBursts;



    }

    prevBursts += task->burst;
    burstTotal += prevBursts;

    count++;


        run(task, task->burst);
        free(task->name); 
        free(task);
    }

    printf("\nAverage Waiting time = %.2f \n", (total/count));
    printf("Average turnAround time = %.2f \n", (burstTotal/count));
    printf("Average response time = %.2f \n", (total/count));



}
