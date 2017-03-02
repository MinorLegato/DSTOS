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

