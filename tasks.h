#ifndef __TASKS_H__
#define __TASKS_H__

#include "kernel.h"
#include "kernel_data.h"

#include <stdlib.h>

// ======================= Task Kernel Functions ======================== //

exception create_task(void (*body)(), uint d) {
    volatile int firstExec = 1;
    // Allocate memory for TCB
    TaskNode* task = allocTask(body, d);
    
    // IF start-up mode THEN
    if (kernelMode == Kernel_start_up) {
        addTask_First(&readyList, task);
        return 1;
    } else  {
        // Disable interrupts
        SaveContext();
        
        if (firstExec) { // IF first execution THEN
            firstExec = 0;
            addTask_First(&readyList, task);
            LoadContext();
        }
    }
    // ENDIF
    // Return status
    return 1;
}

void terminate(void) {
    // Remove running task from Readylist
    delete(removeTask(readyList.pHead->pNext));
    // Set next task to be the running task
    Running = readyList.pHead->pNext->pTask;
    LoadContext();
}

#endif

