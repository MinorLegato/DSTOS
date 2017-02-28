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
    // IF first execution THEN
    if (0) {
        // Set: ìnot first execution any moreî
        // Place running task in the Timerlist
        LoadContext();
    }
    else {
        // IF deadline is reached THEN
        if (0) {
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
    // IF first execution THEN
    if (0) {
        // Set: ìnot first execution any moreî
        Running->DeadLine = nNew;
        // Reschedule Readylist
        LoadContext();
    }
}

#endif

