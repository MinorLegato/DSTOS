#include "kernel_data.h"

mailbox* mb = NULL;

char smsg[100] = "Hello, world!";
char buffer[100];

void s0(void) {
    send_wait(mb, smsg);
    terminate();
}

void r0(void) {
    receive_wait(mb, buffer);
    terminate();
}

void p0(void) {
    printf("%s\n", buffer);
    terminate();
}

int main(void) {
    assert(init_kernel());
    assert(mb = create_mailbox(100, 100));

    assert(create_task(s0, 1000));
    assert(create_task(r0, 500));
    assert(create_task(p0, 2000));

    run();
}

