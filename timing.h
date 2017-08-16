#ifndef __TIMING_H__
#define __TIMING_H__

#include "kernel.h"
#include "kernel_data.h"

// Timing
exception wait(uint nTicks) {
    volatile int isFirst = TRUE;
    isr_off();
    SaveContext();
    if (isFirst) {
        isFirst = FALSE;
        addTask(timerList, getTask(Running));
        LoadContext();
    } else {
        if (Running->DeadLine <= tickCounter) {
            return DEADLINE_REACHED;
        }
    }
    return OK;
}

// Set the tick counter
void set_ticks(uint no_of_ticks) {
    tickCounter = no_of_ticks;
}

// Return the tick counter
uint ticks(void) {
    return tickCounter;
}

// Return the deadline of the current task
uint deadline(void) {
    return Running->DeadLine;
}

// Set deadline for running task3
void set_deadline(uint nNew) {
    volatile int isFirst = TRUE;
    isr_off();
    SaveContext();
    if (isFirst) {
        isFirst = FALSE;
        Running->DeadLine = nNew + tickCounter;
        // Reschedule Readylist
        LoadContext();
    }
}

#endif

