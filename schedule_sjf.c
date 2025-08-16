#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

void swapTask(struct node *p1, struct node *p2)
{
    Task *temp = p1->task;
    p1->task = p2->task;
    p2->task = temp;
}

void selectionSort(struct node **list)
{
    if(*list == NULL){ 
        
        return;
        
        }

    struct node *p1 = *list, *p2;

    struct node *min;

    while (p1 != NULL)
    {

        min = p1;
        p2 = p1->next;

        while (p2 != NULL)
        {

            min = p1;
            p2 = p1->next;

            while (p2 != NULL)
            {

                if (min->task->burst > p2->task->burst)
                {

                    min = p2;
                }
                p2 = p2->next;
            }



        }

        if(min != p1){

            swapTask(p1, min);


        }

        p1 = p1->next;
    }
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

    

    selectionSort(&list);

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
