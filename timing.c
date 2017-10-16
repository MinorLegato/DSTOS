#include "kernel_data.h"

// Timing
exception wait(uint nTicks) {
    volatile int first = TRUE;
    isr_off();
    SaveContext();
    if (first) {
        first = FALSE;
        TaskNode* node = removeTask(getFirstTask(readyList));
        node->nTCnt = nTicks + ticks();
        addTask_nTCnt(timerList, node);
        Running = getFirstTask(readyList)->pTask;
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
        TaskNode* task = removeTask(getFirstTask(readyList));
        task->pTask->DeadLine = nNew;
        addTask_Deadline(readyList, task);
        LoadContext();
    }
}

