#include "kernel.h"

#include <stdio.h>

#include "kernel_data.h"

#include "messages.h"
#include "tasks.h"
#include "timing.h"

#include "kernel_init.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void TimerInt(void)
{
    tickCounter++;
}

int main(void)
{
    TaskList test;

    initTasks(&test);

    for (int i = 0; i < 10; i++) {
        TaskNode* newTask = calloc(1, sizeof *newTask);
        taskDeadline(newTask) = i + 1;
        addTask(&test, newTask);
    }

    TaskNode* iter;

    forTasks(&test, iter) {
        printf("%d", taskDeadline(iter));
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
    return 0;
}

