#include "kernel_data.h"

extern i32 memoryCounter    = 0;
extern i32 kernelMode       = 0;
extern i32 tickCounter      = 0;

extern TaskList*   timerList    = NULL;
extern TaskList*   waitList     = NULL;
extern TaskList*   readyList    = NULL;
extern TCB*        Running      = NULL;

void* alloc(size_t size) {
    void* data ;
    isr_off();
    data = calloc(1, size);
    if (data != NULL) { memoryCounter++; }
    isr_on();
    return data;
}

void delete(void* data) {
    if (data) {
        isr_off();
        free(data);
        memoryCounter--;
        isr_on();
    }
}

void TimerInt(void) {
    TaskNode* iter ;
    tickCounter++;
    
    iter = getFirstTask(timerList);
    
    while (iter != getDummyTask(timerList) && getnTCnt(iter) <= ticks()) {
        addTask_Deadline(readyList, removeTask(iter));
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
//void idleTask() { while (1); }

void isr_off() {  }
void isr_on()  {  }

exception init_kernel(void) { 
    set_ticks(0);
    // Create necessary data structures
    
    if (timerList = allocTaskList(), timerList == NULL) { return FAIL; };
    if (waitList  = allocTaskList(), waitList  == NULL) { return FAIL; };
    if (readyList = allocTaskList(), readyList == NULL) { return FAIL; };
    
    kernelMode = INIT;
    
    // Create an idle task
    if (!create_task(idleTask, 0xFFFFFFFF)) { return FAIL; }
    
    // Set the kernel in start up mode
    
    // Return status
    return SUCCESS;
}

void run(void) {
    // Initialize interrupt timer
    //timer0_start();
    
    // Set the kernel in running mode
    kernelMode = RUNNING;
    
    Running = getFirstTask(readyList)->pTask;
    
    // Enable interrupts
    //    isr_on();
    LoadContext();
}

