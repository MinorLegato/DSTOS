
#ifndef KERNEL_H
#define KERNEL_H


// Debug option
//#define       _DEBUG

/*********************************************************/
/** Global variabels and definitions                     */
/*********************************************************/

#include <stdlib.h>

#ifdef texas_dsp

#define CONTEXT_SIZE    (34 - 2)

#else

#define CONTEXT_SIZE    (13)
#define STACK_SIZE      (100)

#endif

#define TRUE    (1)
#define FALSE   (!TRUE)

#define RUNNING (1)
#define INIT    (!RUNNING)

#define FAIL    (0)
#define SUCCESS (1)
#define OK      (1)

#define DEADLINE_REACHED    (0)
#define NOT_EMPTY           (0)

#define SENDER      (+1)
#define RECEIVER    (-1)

#include "defs.h"
#include "linked_list.h"

typedef i32 exception;
typedef i32 bool;
typedef u32 uint;
typedef i32 action;

struct  l_obj;         // Forward declaration

// Task Control Block, TCB
#ifdef texas_dsp

STRUCT(TCB)
{
	void	(*PC)();
	u32	    *SP;
	u32	    Context[CONTEXT_SIZE];
	u32	    StackSeg[STACK_SIZE];
	u32	    DeadLine;
};


#else


STRUCT(TCB)
{
    u32     Context[CONTEXT_SIZE];        
    u32    *SP;
    void    (*PC)();
    u32     SPSR;     
    u32     StackSeg[STACK_SIZE];
    u32     DeadLine;
};

#endif

// Message items
typedef struct msgobj {
    char            *pData;
    exception       Status;
    struct l_obj    *pBlock;
    struct msgobj   *pPrevious;
    struct msgobj   *pNext;
} msg;

// Mailbox structure
typedef struct {
    msg             *pHead;
    msg             *pTail;
    i32             nDataSize;
    i32             nMaxMessages;
    i32             nMessages;
    i32             nBlockedMsg;
} mailbox;


// Generic list item
typedef struct l_obj {
    TCB             *pTask;
    u32             nTCnt;
    msg             *pMessage;
    struct l_obj    *pPrevious;
    struct l_obj    *pNext;
} listobj;


// Generic list
typedef struct {
    listobj *pHead;
    listobj *pTail;
} list;


// Function prototypes

// Task administration
i32         init_kernel(void);
exception	create_task(void (*body)(), u32 d);
void        terminate(void);
void        run(void);

// Communication
mailbox*	create_mailbox(uint nMessages, uint nDataSize);
i32         no_messages(mailbox* mBox);

exception   send_wait(mailbox* mBox, void* pData);
exception   receive_wait(mailbox* mBox, void* pData);

exception	send_no_wait(mailbox* mBox, void* pData);
i32         receive_no_wait(mailbox* mBox, void* pData);

// Timing
exception	wait(uint nTicks);
void        set_ticks(u32 no_of_ticks);
u32         ticks(void);
u32		    deadline(void);
void        set_deadline(u32 nNew);

//Interrupt
extern void isr_off(void);
extern void isr_on(void);

extern void SaveContext(void);	// Stores DSP registers in TCB pointed to by Running
extern void LoadContext(void);	// Restores DSP registers from TCB pointed to by Running


// ================================== GLOBAL KERNEL DATA ================================= //


STRUCT(TaskList)
{
    TCB task;
    LinkedList list;
};


STRUCT(KernelState)
{
    i32 mode;
    TCB* running;
};


// ==================================== KERNEL FUNCTIONS =============================== //

exception init_kernel(void) 
{ 
    // Set tick counter to zero
    tickCounter = 0;
    // Create necessary data structures
    // TODO
    // Create an idle task
    // Set the kernel in start up mode
    // Return status
    return SUCCESS;
}

exception create_task(void (*body)(), u32 d)
{
    // Allocate memory for TCB
    // Set deadline in TCB
    // Set the TCBís PC to point to the task body
    // Set TCBís SP to point to the stack segment
    // IF start-up mode THEN
    // Insert new task in Readylist
    // Return status
    // ELSE
    // Disable interrupts
    // Save context
    // IF ìfirst executionî THEN
    // Set: ìnot first execution any moreî
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
    // Save context
    // IF first execution THEN
    // Set: înot first execution anymoreî
    // IF receiving task is waiting THEN
    // Copy data to receiving tasksí
    // data area.
    // Remove receiving taskís Message
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
    // Set: ìnot first execution any moreî
    // IF send Message is waiting THEN
    // Copy senderís data to receiving taskís
    // data area
    // Remove sending taskís Message
    // struct from the Mailbox
    // IF Message was of wait type THEN
    // Move sending task to Readylist
    // ELSE
    // Free senderís data area
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
    // Set: ìnot first execution any moreî
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

void set_ticks(u32 no_of_ticks)
{
    // Set the tick counter
    // TODO
}

u32 ticks(void)
{
    // Return the tick counter
    return 0;
}

u32	deadline(void)
{
    // Return the deadline of the current task
    return 0;
}

void set_deadline(u32 nNew)
{
    // Disable interrupt
    // Save context
    // IF first execution THEN
    // Set: ìnot first execution any moreî
    // Set the deadline field in the calling TCB.
    // Reschedule Readylist
    // Load context
    // ENDIF
}

//Interrupt
void isr_off(void)
{
    // ISR ON
}

void isr_on(void)
{
    // ISR OFF
}

#endif
