// main.c
#include "kernel.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>


// ====================================== TASK LIST ===================================== //


typedef struct Tasks {
    TCB     tcb;
    int     firstExec;
    Tasks*  next;
} Tasks;


static void initTasks(Tasks* tasks)
{
    memset(tasks, 0, sizeof *tasks);
}

static void removeTasks(Tasks* tasks)
{
    // TODO
}

static void addTask(Tasks* tcb)
{
    // TODO
}

// ================================== GLOBAL KERNEL DATA ================================= //

enum KernelModes
{
    KERNEL_NOT_RUNNING,
    KERNEL_START_UP,
};

static int tickCounter = 0;

static int  kernelMode  = KERNEL_NOT_RUNNING;

// TODO make sure you can't remove the running task from any list!
static TCB* Running = NULL;

static Tasks readyList;
static Tasks blockedList;

void idleTask() { while (1); }

// ==================================== KERNEL FUNCTIONS =============================== //


exception init_kernel(void) 
{ 
    // Set tick counter to zero
    tickCounter = 0;
    // Create necessary data structures
    initTasks(&readyList);
    initTasks(&blockedList);
    // Create an idle task
    create_task(idleTask, 0xFFFFFFFF);
    // Set the kernel in start up mode
    kernelMode = KERNEL_START_UP;
    // Return status
    return SUCCESS;
}

exception create_task(void (*body)(), uint d)
{
    // Allocate memory for TCB
    TCB* newTask = calloc(1, sizeof *newTask);

    if (newTask == NULL) return 0;
    // Set deadline in TCB
    newTask->DeadLine = d;
    // Set the TCBís PC to point to the task body
    newTask->PC = body;
    // Set TCBís SP to point to the stack segment
    newTask->SP = newTask->StackSeg;
    // IF start-up mode THEN
    if (kernelMode == INIT) {
        // Insert new task in Readylist
        //listPushBack(readyList, newTask, list);
        // Return status
        return 1;
    } else  {
        // Disable interrupts
        SaveContext();

        if (newTask->firstExec) { // IF ìfirst executionî THEN
            // Set: ìnot first execution any moreî
            // Insert new task in Readylist
            // Load context
            LoadContext();
        }
    }
    // ENDIF
    // Return status
    return 1;
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
    // Set: ìnot first execution any moreî
    // IF receiving task is waiting THEN
    // Copy senderís data to the data area
    // of the receivers Message
    // Remove receiving taskís Message
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
    // Set: ìnot first execution any moreî
    // IF send Message is waiting THEN
    // Copy senderís data to receiving taskís
    // data area
    // Remove sending taskís Message
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
    SaveContext();
    // IF first execution THEN
    if (0) {
        // Set: înot first execution anymoreî
        // IF receiving task is waiting THEN
        if (0) {
            // Copy data to receiving tasksí
            // data area.
            // Remove receiving taskís Message
            // struct from the Mailbox
            // Move receiving task to Readylist
            // Load context
        } else {
            // Allocate a Message structure
            // Copy Data to the Message
            // IF mailbox is full THEN
            if (0) {
                // Remove the oldest Message struct
            }
            // Add Message to the Mailbox
        }
    }
    return SUCCESS;
}

i32 receive_no_wait(mailbox* mBox, void* pData)
{
    // Disable interrupt
    SaveContext();
    // IF first execution THEN
    if (0) {
        // Set: ìnot first execution any moreî
        // IF send Message is waiting THEN
        if (0) {
            // Copy senderís data to receiving taskís
            // data area
            // Remove sending taskís Message
            // struct from the Mailbox
            // IF Message was of wait type THEN
            if (0) {
                // Move sending task to Readylist
            }        
            else {
                // Free senderís data area
            }       
        }
        LoadContext();
    }
    // Return status on received Message
    return 0;
}

// Timing
exception wait(uint nTicks)
{
    // Disable interrupt
    SaveContext();
    // IF first execution THEN
    if (0) {
        // Set: ìnot first execution any moreî
        // Place running task in the Timerlist
        LoadContext();
    }
    else {
        // IF deadline is reached THEN
        if (0) {
            // Status is DEADLINE_REACHED
        }
        else {
            // Status is OK
        }
    }
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
    if (0) {
        // Set: ìnot first execution any moreî
        Running->DeadLine = nNew;
        // Reschedule Readylist
        LoadContext();
    }
}

//FUCKANTON
// =====================================  MAIN ======================================= //


void TimerInt(void)
{
    tickCounter++;
}


int main(void)
{
    init_kernel();
    run();

    while (1)
    {
        SaveContext();
        TimerInt();
        LoadContext();
    }

    return 0;
}
