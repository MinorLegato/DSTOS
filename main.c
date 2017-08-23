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
        TimerInt();

        addTask_nTCnt(tasks, allocTask(NULL, 16 - i));
        
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
    }
    */
}

