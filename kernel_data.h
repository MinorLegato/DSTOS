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

#define forTasks(HEAD, ITER) for ((ITER) = (HEAD)->next; (ITER) != (HEAD); (ITER) = (ITER)->next)

static void initTasks(Tasks* head)
{
    head = calloc(1, sizeof *head);
    head->next = head;

    printf("%a\n", head);
    printf("%a\n", head->next);
}

static Tasks* removeTask(Tasks* task, Tasks* prev)
{
    Tasks* removedTask = task;
    prev->next = task->next;
    return removedTask;
}

static int noTasks(Tasks* head)
{
    return head == head->next;
}

static void addTask(Tasks* head, Tasks* task)
{
    task->next = head->next;
    head->next = task;
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

