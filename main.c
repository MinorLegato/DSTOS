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

void TimerInt(void) { tickCounter++; }

int main(void) {
    //char strBuffer[] = "Hello, world!";

    mailbox* mBox = create_mailbox(10, 20);
    
    create_msg_first(mBox, "1!\n");
    create_msg_first(mBox, "2!\n");
    create_msg_first(mBox, "3!\n");
    create_msg_last(mBox, "4!\n");
    create_msg_first(mBox, "5!\n");
    create_msg_first(mBox, "4!\n");

    msg* iter = getFirstMsg(mBox);

    while (iter != mBox->pTail) {
        printf(iter->pData);
        iter = iter->pNext;
    }

    printf("DONE");

    /*
    init_kernel();
    run();
    
    while (1) {
        SaveContext();
        TimerInt();
        LoadContext();
    }*/
}

