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

static void t0() {
    static char str[] = "Hello, world!";
    send_wait(mBox, str);
    terminate();
}

static void t1() {
    static char str[100];
    receive_wait(mBox, str);
    printf(str);
    terminate();
}

void TimerInt(void) { tickCounter++; }

int main(void) {
    if (!init_kernel()) { printf("init_kernel: FAIL"); }

    mBox = create_mailbox(100, 100);

    create_task(t0, 10);
    create_task(t1, 100);

    run();

    while (1) {
        SaveContext();
        TimerInt();
        LoadContext();
    }
}

