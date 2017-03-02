#ifndef __TASKS_H__
#define __TASKS_H__

#include "kernel.h"
#include "kernel_data.h"

#include <stdlib.h>


exception create_task(void (*body)(), uint d)
{
    // Allocate memory for TCB
    Tasks* newTask = calloc(1, sizeof *newTask);

    if (newTask == NULL) return 0;
    // Set deadline in TCB
    newTask->tcb.DeadLine = d;
    // Set the TCBís PC to point to the task body
    newTask->tcb.PC = body;
    // Set TCBís SP to point to the stack segment
    newTask->tcb.SP = newTask->tcb.StackSeg;
    // IF start-up mode THEN
    if (kernelMode == INIT) {
        // Insert new task in Readylist
        // TODO 
        // Return status
        return 1;
    } else  {
        // Disable interrupts
        SaveContext();

        if (newTask->firstExec) { // IF ìfirst executionî THEN
            // Set: ìnot first execution any moreî
            // Insert new task in Readylist
            // Load context
            LoadContext();
        }
    }
    // ENDIF
    // Return status
    return 1;
}

void terminate(void)
{
    // Remove running task from Readylist
    // Set next task to be the running task
    // Load context
}


#endif

