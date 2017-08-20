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
    mailbox* mBox = create_mailbox(100, 100);

    if (no_messages(mBox)) { printf("\nEMPTY\n"); }

    msgPushBack(mBox, createMsg("1!\n"));
    msgPushBack(mBox, createMsg("2!\n"));
    msgPushBack(mBox, createMsg("3!\n"));
    msgPushBack(mBox, createMsg("4!\n"));
    msgPushBack(mBox, createMsg("5!\n"));

    if (no_messages(mBox)) { printf("\nEMPTY\n"); }

    msg* m;
    forEach(m, mBox) { printf(m->pData); }

    msgPopFront(mBox);
    msgPopBack(mBox);

    printf("\n\n");
    forReve(m, mBox) { printf(m->pData); }

    if (no_messages(mBox)) { printf("\nEMPTY\n"); }

    printf("\nDONE");

    /*
    init_kernel();
    run();
    
    while (1) {
        SaveContext();
        TimerInt();
        LoadContext();
    }*/
}

