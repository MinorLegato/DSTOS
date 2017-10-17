#include "kernel_data.h"

mailbox* mb = NULL;

char msg1[100] = "msg1";
char msg2[100] = "msg2";
char msg3[100] = "msg3";

char buffer1[100];
char buffer2[100];
char buffer3[100];

void s0() {
    send_no_wait(mb, msg1);
    send_no_wait(mb, msg2);
    send_no_wait(mb, msg3);
    terminate();
}

void r0() {
    wait(1000);
    receive_no_wait(mb, buffer1);
    receive_no_wait(mb, buffer2);
    receive_no_wait(mb, buffer3);
    terminate();
}

int main(void) {
    init_kernel();
    mb = create_mailbox(2, 100);
    
    create_task(s0, 5000);
    create_task(r0, 10000);
    
    run();
}

