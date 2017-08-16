#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__

#include "kernel.h"
#include "tools.h"
#include "list_ops.h"

enum Kernel_modes {
    Kernel_not_running,
    Kernel_start_up,
    Kernel_running
};

TaskList timerList;
TaskList waitList;
TaskList readyList;

TCB* Running = NULL;

i32 tickCounter = 0;

i32 kernelMode  = Kernel_not_running;

void idleTask() { while (1); }

#endif

