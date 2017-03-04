#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__

#include "kernel.h"
#include "list_ops.h"

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

