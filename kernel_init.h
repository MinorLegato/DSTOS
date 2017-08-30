#ifndef __KERNEL_INIT_H__
#define __KERNEL_INIT_H__

#include "kernel.h"
#include "kernel_data.h"

exception init_kernel(void) { 
    set_ticks(0);
    // Set tick counter to zero
    tickCounter = 0;
    // Create necessary data structures
    if (timerList = allocTaskList(), timerList == NULL) { return FAIL; };
    if (waitList  = allocTaskList(), waitList  == NULL) { return FAIL; };
    if (readyList = allocTaskList(), readyList == NULL) { return FAIL; };
    // Create an idle task
    if (!create_task(idleTask, 0xFFFFFFFF)) { return FAIL; }
    // Set the kernel in start up mode
    kernelMode = INIT;
    // Return status
    return SUCCESS;
}

void run(void) {
    // Initialize interrupt timer
    // Set the kernel in running mode
    kernelMode = RUNNING;
    // Enable interrupts
    isr_on();

    Running = getFirstTask(readyList)->pTask;

    LoadContext();
}

#endif
