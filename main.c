#include "kernel.h"
#include "tools.h"

#include <stdio.h>

#include "kernel_data.h"

#include "messages.h"
#include "tasks.h"
#include "timing.h"

#include "kernel_init.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void TimerInt(void) { tickCounter++; }

int main(void) {
    TaskList list; initTaskList(&list);
    TaskNode* node = NULL;
    
    for (int i = 1; i < 15; i++) {
        if (node = allocTask(idleTask, i*10)) {
            addTask_Deadline(&list, node);
        }
    }
    
    node = list.pHead->pNext;
    while (node != list.pTail){
        printf("%d\n", node->pTask->DeadLine);
        node = node->pNext;
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
