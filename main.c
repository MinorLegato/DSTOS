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

void TimerInt(void) {
    tickCounter++;
}

int main(void) {
    /*
    ARRAY(i32, 32) arr = {0};
    for (i32 i = 0; i < 10; i++) { PUSH(&arr, i + 1); }
    MOVE(&arr, 5, 2);
    for (i32 i = 0; i < SIZE(&arr); i++) { printf("%d\n", *GET(&arr, i)); }
    */

    init_kernel();
    run();

    while (1) {
        SaveContext();
        TimerInt();
        LoadContext();
    }

    return 0;
}

