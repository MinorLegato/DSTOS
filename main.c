#include "messages.c"
#include "tasks.c"
#include "timing.c"
#include "kernel_init.h"

mailbox* mb = NULL;

void s0(void) {
    char msg[100] = "Hello, world!";
    send_wait(mb, msg);
    terminate();
}

void r0(void) {
    char buffer[100];
    receive_no_wait(mb, buffer);
    printf("%s\n", buffer);
    terminate();
}

int main(void) {
    assert(init_kernel());
    assert(mb = create_mailbox(100, 100));

    assert(create_task(s0, 1000));
    assert(create_task(r0, 2000));

    run();
}

