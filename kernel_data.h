#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__

#include "kernel.h"

// ================================== ================= ================================= //

/*
typedef struct Tasks {
    TCB             tcb;
    struct Tasks*   next;
} Tasks;


#define getTask(T)      ((Tasks*)((int*)(T) - 1))

#define isFirstExec(T)  (getTask(T)->firstExec)
#define deflowerTask(T) (getTask(T)->firstExec = 0)

#define forTasks(HEAD, ITER) for ((ITER) = (HEAD)->next; (ITER) != (HEAD); (ITER) = (ITER)->next)


static void initTasks(Tasks* head)
{
    memset(head, 0, sizeof *head);
    head->next = head;
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

static inline uint taskDeadline(const Tasks* task)
{
    return task->tcb.DeadLine;
}

static Tasks* findLowestDeadline(const Tasks* head)
{
    Tasks* lowest = head->next;

    Tasks* iter = NULL;

    forTasks(head, iter)
        if (taskDeadline(iter) < taskDeadline(lowest))
            lowest = iter;

    return lowest;
}

static Tasks* removeTask(Tasks* head, Tasks* task)
{
    Tasks* prev = head;
    Tasks* iter = head->next;

    while (iter != head) {
        if (iter == task) {
            prev->next = iter->next;
            return iter;
        }
        prev = iter;
        iter = iter->next;
    }

    return NULL;
}

*/

// ================================== GLOBAL KERNEL DATA ================================= //

enum KernelModes
{
    KERNEL_NOT_RUNNING,
    KERNEL_START_UP,
};


TCB* Running = NULL;

int tickCounter = 0;

int  kernelMode  = KERNEL_NOT_RUNNING;

TaskList* readyList = NULL;
TaskList* waitList  = NULL;
TaskList* timerList = NULL;

void idleTask() { while (1); }

#endif

