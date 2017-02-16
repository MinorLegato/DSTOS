// main.c
#include "kernel.h"

TCB taskA;
TCB * Running;

void task1(void);

i32 tickCounter = 0;

void TimerInt (void)
{
    tickCounter++;
    //Check the Timerlist for tasks that are ready for
    //execution, move these to Readylist
    //Check the Waitinglist for tasks that have expired
    //deadlines, move these to Readylist and clean up
    //their Mailbox entry.
}

int main(void)
{
	//Running = &taskA;
	//Running->PC = task1;
	//Running->SP = &(Running->StackSeg[STACK_SIZE-1]);

	//LoadContext();

    while (1) {
        SaveContext();
        TimerInt();
        LoadContext();
    }
}

