#ifndef __KERNEL_INIT_H__
#define __KERNEL_INIT_H__

#include "kernel.h"
#include "kernel_data.h"

exception init_kernel(void) { 
    // Set tick counter to zero
    tickCounter = 0;
    // Create necessary data structures
    initTaskManager(&taskManager);
    // Create an idle task
    create_task(idleTask, 0xFFFFFFFF);
    // Set the kernel in start up mode
    kernelMode = Kernel_start_up;
    // Return status
    return SUCCESS;
}


void run(void) {
    // Initialize interrupt timer
    // Set the kernel in running mode
    kernelMode = Kernel_running;
    // Enable interrupts
    LoadContext();
}

#endif
