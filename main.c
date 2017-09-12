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

#define TEST_PATTERN_1 0xAA
#define TEST_PATTERN_2 0x55

mailbox* mb = NULL;

void t0(void){
    static char msg[100] = "Hello, world!";

    send_wait(mb, msg);
    
    wait(500);
    
    terminate();
}

void t1(void) {
    static char buffer[100];

    receive_wait(mb, buffer);

    printf("%s\n", buffer);

    wait(1000);
    
    terminate();
}

int main(void) {
    assert(init_kernel());
    assert(mb = create_mailbox(100, 100));

    assert(create_task(t0, 100));
    assert(create_task(t1, 150));

    run();

    while (1) { SaveContext(); TimerInt(); LoadContext(); }
}

