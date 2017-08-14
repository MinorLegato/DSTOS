#ifndef __TASKS_H__
#define __TASKS_H__

#include "kernel.h"
#include "kernel_data.h"

#include <stdlib.h>

// =============================== Task Kernel Functions ================================ //

exception create_task(void (*body)(), uint d) {
    volatile int firstExec = 1;
    // Allocate memory for TCB
    int taskIndex = newTask(&taskManager);

    TCB* tcb = getTCB(&taskManager, taskIndex);

    if (tcb == NULL) return 0;
    // Set deadline in TCB
    tcb->DeadLine = d;
    // Set the TCBís PC to point to the task body
    tcb->PC = body;
    // Set TCBís SP to point to the stack segment
    tcb->SP = tcb->StackSeg;
    // IF start-up mode THEN
    if (kernelMode == INIT) {
        insertToReadyList(&taskManager, taskIndex);
        return 1;
    } else  {
        // Disable interrupts
        SaveContext();

        if (firstExec) { // IF ìfirst executionî THEN
            firstExec = 0;
            insertToReadyList(&taskManager, taskIndex);
            LoadContext();
        }
    }
    // ENDIF
    // Return status
    return 1;
}

void terminate(void) {
    // Remove running task from Readylist
    // Set next task to be the running task
    LoadContext();
}


#endif

