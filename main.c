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
    static char data[] = "from task 1!";

    send_wait(mBox, data);
    wait(10);

    terminate();
}

static void t1() {
    static char data[100];

    receive_wait(mBox, data);
    printf("%s\n", data);
    wait(10);

    terminate();
}

static void t2() {
    static char data[] = "from task 2!";

    send_wait(mBox, data);
    wait(10);

    terminate();
}

static void t3() {
    static char data[100];

    receive_wait(mBox, data);
    wait(10);
    printf("%s\n", data);

    terminate();
}

int main(void) {
    assert(init_kernel());
    assert(mBox = create_mailbox(100, 100));

    create_task(t0, 1);
    create_task(t1, 3);
    create_task(t2, 4);
    create_task(t3, 5);

    run();

    while (1) { SaveContext(); TimerInt(); LoadContext(); }
}

