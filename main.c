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

static mailbox* mBox = NULL;

static void t0() { printf("task 0\n"); terminate(); }
static void t1() { printf("task 1\n"); terminate(); }
static void t2() { printf("task 2\n"); terminate(); }
static void t3() { printf("task 3\n"); terminate(); }
static void t4() { printf("task 4\n"); terminate(); }
static void t5() { printf("task 5\n"); terminate(); }
static void t6() { printf("task 6\n"); terminate(); }
static void t7() { printf("task 7\n"); terminate(); }
static void t8() { printf("task 8\n"); terminate(); }
static void t9() { printf("task 9\n"); terminate(); }

void TimerInt(void) { tickCounter++; }

int main(void) {
    if (!init_kernel()) { printf("init_kernel: FAIL"); }

    create_task(t0, rand());
    create_task(t1, rand());
    create_task(t2, rand());
    create_task(t3, rand());
    create_task(t4, rand());
    create_task(t5, rand());
    create_task(t6, rand());
    create_task(t7, rand());
    create_task(t8, rand());
    create_task(t9, rand());

    run();

    while (1) {
        SaveContext();
        TimerInt();
        LoadContext();
    }
}

