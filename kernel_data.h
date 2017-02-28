#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__


#include "kernel.h"

#include <string.h>


// ================================== ================= ================================= //

typedef struct Tasks {
    TCB     tcb;
    int     firstExec;
    struct Tasks*  next;
} Tasks;


static void initTasks(Tasks* tasks)
{
    memset(tasks, 0, sizeof *tasks);
}

static void removeTasks(Tasks* tasks)
{
    // TODO
}

static void addTask(Tasks* tcb)
{
    // TODO
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

Tasks readyList;
Tasks blockedList;


void idleTask() { while (1); }


#endif

