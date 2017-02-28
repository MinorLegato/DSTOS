#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__

#include "kernel.h"
#include <string.h>


// ================================== ================= ================================= //

typedef struct Tasks {
    int            firstExec;
    TCB            tcb;
    struct Tasks*  next;
} Tasks;


#define getTask(T)      ((Tasks*)((int*)(T) - 1))

#define isFirstExec(T)  (getTask(T)->firstExec)
#define deflowerTask(T) (getTask(T)->firstExec = 0)

#define iterateTasks(HEAD) for (Tasks* iter = (HEAD)->next; iter != (HEAD); iter = iter->next)

static void initTasks(Tasks* head)
{
    head = calloc(1, sizeof *head);
    head->next = head;
}

static Tasks* removeTask(Tasks* task, Tasks* prev)
{
    Tasks* removedTask = tasks;

    prev->next = task->next;

    return removedTask;
}

static int noTasks(Tasks* )
{
    return head == head->next;
}

static void pushTask(Tasks* head, Tasks* task)
{
}


// ================================== GLOBAL KERNEL DATA ================================= //

enum KernelModes
{
    KERNEL_NOT_RUNNING,
    KERNEL_START_UP,
};


TCB* Running = NULL;

int tickCounter = 0;

int  kernelMode  = KERNEL_NOT_RUNNING;

Tasks* readyList = NULL;
Tasks* waitList  = NULL;
Tasks* timerList = NULL;

void idleTask() { while (1); }

#endif

