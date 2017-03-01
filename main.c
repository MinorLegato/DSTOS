// main.c

#include "kernel.h"

#include <stdio.h>

#include "kernel_data.h"
#include "kernel_init.h"
#include "messages.h"
#include "tasks.h"
#include "timing.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>


void TimerInt(void)
{
    tickCounter++;
}


int main()
{
    Tasks* testList; initTasks(testList);

    for (int i = 0; i < 10; i++) {
        Tasks* newTask = calloc(1, sizeof *newTask);
        
        newTask->firstExec = i + 1;

        if (newTask != NULL)
            addTask(testList, newTask);
    }

    Tasks* iter = testList->next;

    while (iter != testList) {
        printf("%d\n", iter->firstExec);
        iter = iter->next;
    }
}

/*
int main(void)
{
    init_kernel();
    run();

    while (1) {
        SaveContext();
        TimerInt();
        LoadContext();
    }

    return 0;
}
*/

