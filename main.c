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

#include <string.h>

mailbox* mb = NULL;

void t0(void);
void t1(void);

void t0(void){
    char msg[100] = "Hello, world!";

    send_wait(mb, msg);
    
    terminate();
}

void t1(void) {
    char buffer[100];

    receive_wait(mb, buffer);

    printf("%s\n", buffer);
    
    terminate();
}

int main(void) {
    assert(init_kernel());
    assert(mb = create_mailbox(100, 100));

    assert(create_task(t0, 100));
    assert(create_task(t1, 150));

    assert(create_task(t0, 500));
    assert(create_task(t1, 700));

    run();

    while (1) { SaveContext(); TimerInt(); LoadContext(); }
}

