#include "kernel_data.h"

mailbox* mb = NULL;

char smsg[100] = "Hello, world!";
char buffer[100];

void s0() {
    send_no_wait(mb, smsg);
    terminate();
}

void r0() {
    receive_no_wait(mb, buffer);
    terminate();
}

int main(void) {
    assert(init_kernel());
    assert(mb = create_mailbox(100, 100));

    assert(create_task(s0, 500));
    assert(create_task(r0, 1000));
  
    run();
}

