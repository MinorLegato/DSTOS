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
    char strBuffer[] = "Hello, world!";
    
    mailbox* mBox = create_mailbox(10, 20);
    
    create_msg_first(mBox, strBuffer);
    
    printf(getFirstMsg(mBox)->pData);
    
    /*
    init_kernel();
    run();
    
    while (1) {
        SaveContext();
        TimerInt();
        LoadContext();
    }*/
}
