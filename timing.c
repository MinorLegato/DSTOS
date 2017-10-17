#include "kernel_data.h"

exception wait(uint nTicks) {
    volatile int first = TRUE;
    isr_off();
    SaveContext();
    if (first) {
        TaskNode* node;
        first = FALSE;
        node = removeTask(getFirstTask(readyList));
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

void set_ticks(uint no_of_ticks) {
    tickCounter = no_of_ticks;
}

uint ticks(void) {
    return tickCounter;
}

uint deadline(void) {
    return Running->DeadLine;
}

void set_deadline(uint nNew) {
    volatile int isFirst = TRUE;
    isr_off();
    SaveContext();
    if (isFirst) {
        TaskNode* task;
        isFirst = FALSE;
        task = removeTask(getFirstTask(readyList));
        task->pTask->DeadLine = nNew;
        addTask_Deadline(readyList, task);
        LoadContext();
    }
}

