#ifndef __TASKS_H__
#define __TASKS_H__

#include "kernel.h"
#include "kernel_data.h"

#include <stdlib.h>

// =============================== Task Kernel Functions ================================ //

exception create_task(void (*body)(), uint d) {
    volatile int firstExec = 1;
    // Allocate memory for TCB
    TaskNode *task = calloc(1, sizeof *task);
    if (task == NULL) return 0;
    
    TCB *tcb = calloc(1, sizeof *tcb);
    if (tcb == NULL) { free(task); return 0; }
    
    task->pTask = tcb;
    // Set deadline in TCB
    tcb->DeadLine = d;
    // Set the TCB's PC to point to the task body
    tcb->PC = body;
    // Set TCB's SP to point to the stack segment
    tcb->SP = tcb->StackSeg;
    // IF start-up mode THEN
    if (kernelMode == Kernel_start_up) {
        addTask(&readyList, task);
        return 1;
    } else  {
        // Disable interrupts
        SaveContext();
        
        if (firstExec) { // IF first execution THEN
            firstExec = 0;
            addTask(&readyList, task);
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

