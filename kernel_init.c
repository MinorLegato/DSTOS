#include "kernel_data.h"

extern i32 kernelMode   = 0;
extern i32 tickCounter  = 0;

extern TaskList*   timerList    = NULL;
extern TaskList*   waitList     = NULL;
extern TaskList*   readyList    = NULL;
extern TCB*        Running      = NULL;

void TimerInt(void) {
    tickCounter++;

    TaskNode* iter = getFirstTask(timerList);

    while (iter != getDummyTask(timerList) && getnTCnt(iter) <= ticks()) {
        addTask_nTCnt(readyList, removeTask(iter));
        iter = getFirstTask(timerList);
    }

    iter = getFirstTask(waitList);

    while (iter != getDummyTask(waitList) && getDeadline(iter) <= ticks()) {
        addTask_Deadline(readyList, removeTask(iter));
        iter = getFirstTask(waitList);
    }

    Running = getFirstTask(readyList)->pTask;
}

void idleTask() { while (1) { SaveContext(); TimerInt(); LoadContext(); } }

void isr_off() {  }
void isr_on()  {  }

exception init_kernel(void) { 
    set_ticks(0);
    // Create necessary data structures
    
    if (timerList = allocTaskList(), timerList == NULL) { return FAIL; };
    if (waitList  = allocTaskList(), waitList  == NULL) { return FAIL; };
    if (readyList = allocTaskList(), readyList == NULL) { return FAIL; };

    // Create an idle task
    if (!create_task(idleTask, 0xFFFFFFFF)) { return FAIL; }

    // Set the kernel in start up mode
    kernelMode = INIT;

    // Return status
    return SUCCESS;
}

void run(void) {
    // Initialize interrupt timer
    // Set the kernel in running mode
    kernelMode = RUNNING;

    Running = getFirstTask(readyList)->pTask;

    // Enable interrupts
    isr_on();
    LoadContext();
}

