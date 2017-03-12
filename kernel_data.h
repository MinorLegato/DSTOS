#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__

#include "kernel.h"
//#include "list_ops.h"
#include "task_manager.h"

// ================================== GLOBAL KERNEL DATA ================================= //

enum KernelModes
{
    KERNEL_NOT_RUNNING,
    KERNEL_START_UP,
    KERNEL_RUNNING
};


TCB* Running = NULL;

int tickCounter = 0;

int  kernelMode  = KERNEL_NOT_RUNNING;

TaskManager taskManager;

int readySize = 0;
TCB* readyList = NULL;

int waitSize = 0;
TCB* waitList  = NULL;

int timerSize = 0;
TCB* timerList = NULL;

void idleTask() { while (1); }

#endif

