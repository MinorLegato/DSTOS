#ifndef __TIMING_H__
#define __TIMING_H__

#include "kernel.h"
#include "kernel_data.h"
//FUCKANTON

// Timing
exception wait(uint nTicks)
{
    // Disable interrupt
    SaveContext();
    if (isFirstExec(Running)) {
        deflowerTask(Running);
        addTask(timerList, getTask(Running));
        LoadContext();
    }
    else {
        if (Running->DeadLine <= tickCounter) {
            // Status is DEADLINE_REACHED
        }
        else {
            // Status is OK
        }
    }
    // Return status
    return 0;
}

// Set the tick counter
void set_ticks(uint no_of_ticks)
{
    tickCounter = no_of_ticks;
}

// Return the tick counter
uint ticks(void)
{
    return tickCounter;
}

// Return the deadline of the current task
uint deadline(void)
{
    return Running->DeadLine;
}

// Set deadline for running task3
void set_deadline(uint nNew)
{
    // Disable interrupt
    SaveContext();
    if (isFirstExec(Running)) {
        deflowerTask(Running);
        Running->DeadLine = nNew + tickCounter;
        // Reschedule Readylist
        LoadContext();
    }
}

#endif

