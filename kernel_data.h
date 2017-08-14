#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__

#include "kernel.h"
#include "task_manager.h"

// ================================== GLOBAL KERNEL DATA ================================= //

enum Kernel_modes {
    Kernel_not_running,
    Kernel_start_up,
    Kernel_running
};


TCB* Running = NULL;

i32 tickCounter = 0;

i32  kernelMode  = Kernel_not_running;

TaskManager taskManager;

i32 readySize = 0;
TCB* readyList = NULL;

i32 waitSize = 0;
TCB* waitList  = NULL;

i32 timerSize = 0;
TCB* timerList = NULL;

void idleTask() { while (1); }

#endif

