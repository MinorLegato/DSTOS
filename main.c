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

mailbox* mBox = NULL;

static void t0() {
    static char snd[] = "from task 1!";
    static char rec[100];

    send_wait(mBox, snd);

    receive_wait(mBox, rec);
    printf("%s\n", rec);

    terminate();
}

static void t1() {
    static char snd[] = "from task 2!";
    static char rec[100];

    receive_wait(mBox, rec);

    printf("%s\n", rec);
    send_wait(mBox, snd);

    terminate();
}

int main(void) {
    assert(init_kernel());
    assert(mBox = create_mailbox(100, 100));

    create_task(t0, 10);
    create_task(t1, 100);

    run();
}

