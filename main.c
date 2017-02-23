// main.c
#include "kernel.h"
#include "defs.h"

#include "LinkedList.h"

// ================================== GLOBAL KERNEL DATA ================================= //

static i32 tickCounter;


STRUCT(TaskList)
{
    TCB task;
    LinkedList list;
};


static int  kernelMode  = INIT;
static TCB* Running    = NULL;

static TaskList readyList;
static TaskList blockedList;

void idleTask() { while (1); }


// ==================================== KERNEL FUNCTIONS =============================== //


exception init_kernel(void) 
{ 
    // Set tick counter to zero
    tickCounter = 0;
    // Create necessary data structures
    // Create an idle task
    // Set the kernel in start up mode
    kernelMode = START_UP_MODE;
    // Return status
    return SUCCESS;
}

exception create_task(void (*body)(), uint d)
{
    // Allocate memory for TCB
    TCB* newTcb = malloc(sizeof);
    // Set deadline in TCB
    // Set the TCB�s PC to point to the task body
    // Set TCB�s SP to point to the stack segment
    // IF start-up mode THEN
    // Insert new task in Readylist
    // Return status
    // ELSE
    // Disable interrupts
    // Save context
    // IF �first execution� THEN
    // Set: �not first execution any more�
    // Insert new task in Readylist
    // Load context
    // ENDIF
    // ENDIF
    // Return status
    // return SUCCESS;
}

void terminate(void)
{
    // Remove running task from Readylist
    // Set next task to be the running task
    // Load context
}


void run(void)
{
    // Initialize interrupt timer
    // Set the kernel in running mode
    // Enable interrupts
    // Load context
}

mailbox* create_mailbox(uint nMessages, uint nDataSize)
{
    // Allocate memory for the Mailbox
    // Initialize Mailbox structure
    // Return Mailbox*
    return NULL;
}

i32 no_messages(mailbox* mBox)
{
    // IF Mailbox is empty THEN
    // Free the memory for the Mailbox
    // Return OK
    // ELSE
    // Return NOT_EMPTY
    // ENDIF
    return 0;
}

exception send_wait(mailbox* mBox, void* pData)
{
    // Disable interrupt
    // Save context
    // IF first execution THEN
    // Set: �not first execution any more�
    // IF receiving task is waiting THEN
    // Copy sender�s data to the data area
    // of the receivers Message
    // Remove receiving task�s Message
    // struct from the mailbox
    // Move receiving task to Readylist
    // ELSE
    // Allocate a Message structure
    // Set data pointer
    // Add Message to the Mailbox
    // Move sending task from Readylist to
    // Waitinglist
    // ENDIF
    // Load context
    // ELSE
    // IF deadline is reached THEN
    // Disable interrupt
    // Remove send Message
    // Enable interrupt
    // Return DEADLINE_REACHED
    // ELSE
    // Return OK
    // ENDIF
    // ENDIF
    return SUCCESS;
}

exception receive_wait(mailbox* mBox, void* pData)
{
    // Disable interrupt
    // Save context
    // IF first execution THEN
    // Set: �not first execution any more�
    // IF send Message is waiting THEN
    // Copy sender�s data to receiving task�s
    // data area
    // Remove sending task�s Message
    // struct from the Mailbox
    // IF Message was of wait type THEN
    // Move sending task to Ready list
    // ELSE
    // Free senders data area
    // ENDIF
    // ELSE
    // Allocate a Message structure
    // Add Message to the Mailbox
    // Move receiving task from Readylist to
    // Waitinglist
    // ENDIF
    // Load context
    // ELSE
    // IF deadline is reached THEN
    // Disable interrupt
    // Remove receive Message
    // Enable interrupt
    // Return DEADLINE_REACHED
    // ELSE
    // Return OK
    // ENDIF
    // ENDIF
    return SUCCESS;
}

exception send_no_wait(mailbox* mBox, void* pData)
{
    // Disable interrupt
    // Save context
    // IF first execution THEN
    // Set: �not first execution anymore�
    // IF receiving task is waiting THEN
    // Copy data to receiving tasks�
    // data area.
    // Remove receiving task�s Message
    // struct from the Mailbox
    // Move receiving task to Readylist
    // Load context
    // ELSE
    // Allocate a Message structure
    // Copy Data to the Message
    // IF mailbox is full THEN
    // Remove the oldest Message struct
    // ENDIF
    // Add Message to the Mailbox
    // ENDIF
    // ENDIF
    return SUCCESS;
}

i32 receive_no_wait(mailbox* mBox, void* pData)
{
    // Disable interrupt
    // Save context
    // IF first execution THEN
    // Set: �not first execution any more�
    // IF send Message is waiting THEN
    // Copy sender�s data to receiving task�s
    // data area
    // Remove sending task�s Message
    // struct from the Mailbox
    // IF Message was of wait type THEN
    // Move sending task to Readylist
    // ELSE
    // Free sender�s data area
    // ENDIF
    // ENDIF
    // Load context
    // ENDIF
    // Return status on received Message
    return 0;
}

// Timing
exception wait(uint nTicks)
{
    // Disable interrupt
    // Save context
    // IF first execution THEN
    // Set: �not first execution any more�
    // Place running task in the Timerlist
    // Load context
    // ELSE
    // IF deadline is reached THEN
    // Status is DEADLINE_REACHED
    // ELSE
    // Status is OK
    // ENDIF
    // ENDIF
    // Return status
    return 0;
}

// Set the tick counter
void set_ticks(u32 no_of_ticks)
{
    tickCounter = no_of_ticks;
}

// Return the tick counter
u32 ticks(void)
{
    return tickCounter;
}

// Return the deadline of the current task
u32 deadline(void)
{
    return Running->DeadLine;
}

// Set deadline for running task3
void set_deadline(u32 nNew)
{
    // Disable interrupt
    SaveContext();
    // IF first execution THEN
    // Set: �not first execution any more�
    // ENDIF
    Running->DeadLine = nNew;
    // Reschedule Readylist
    LoadContext();
    // ENDIF
}

// =====================================  MAIN ======================================= //


void TimerInt(void)
{
    tickCounter++;
}


int main(void)
{

    while (1)
    {
        SaveContext();
        TimerInt();
        LoadContext();
    }

    return 0;
}
