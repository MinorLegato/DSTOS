#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__

#include "kernel.h"

// ================================== ================= ================================= //


typedef struct Tasks {
    TCB     tcb;
    int     firstExec;
    Tasks*  next;
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

static int tickCounter = 0;

static int  kernelMode  = KERNEL_NOT_RUNNING;

// TODO make sure you can't remove the running task from any list!
static TCB* Running = NULL;

static Tasks readyList;
static Tasks blockedList;

void idleTask() { while (1); }


#endif

