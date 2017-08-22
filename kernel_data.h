#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__

#include "kernel.h"
#include "tools.h"
#include "list_ops.h"

enum Kernel_states {
    Kernel_start_up,
    Kernel_running
};

TaskList* timerList = NULL;
TaskList* waitList = NULL;
TaskList* readyList = NULL;

TCB* Running = NULL;

i32 tickCounter = 0;

i32 kernelMode  = Kernel_start_up;

void idleTask() { while (1); }

#endif

