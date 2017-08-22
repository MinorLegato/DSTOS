#include "kernel.h"
#include "tools.h"

#include <stdio.h>

#include "kernel_data.h"

void isr_off() {}
void isr_on()  {}

#include "messages.h"
#include "tasks.h"
#include "timing.h"

#include "kernel_init.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void TimerInt(void) { tickCounter++; }

int main(void) {
    TaskList* tasks = allocTaskList();

    for (int i = 0; i < 16; i++) {
        //TaskNode* node = alloc(sizeof *node);
        //node->pTask = alloc(sizeof *node->pTask);
        //node->pTask->DeadLine = i + 1;
        //addTask_Deadline(tasks, node);
        addTask_Deadline(tasks, allocTask(NULL, i + 1));
        
        printTaskList(tasks);
        printf("\n\n");
    }

    /*
    init_kernel();
    run();
    
    while (1) {
        SaveContext();
        TimerInt();
        LoadContext();
    }*/
}

