
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

#define "defs.h"

typedef i32             exception;
typedef i32             bool;
typedef unsigned i32    uint;
typedef i32 			action;

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


exception init_kernel(void) 
{ 
    // TODO
    return SUCCESS;
}

exception create_task(void (*body)(), u32 d)
{
    TCB* tcb = malloc(sizeof (TCB));
    if (tcb == NULL) { return FAIL; }

    asm ( mov r0, r1);

    tcb->DeadLine = d;
    tcb->PC = body;

    return SUCCESS;
}

void terminate(void)
{
    // TODO
}

void run(void)
{
    // TODO
}

mailbox* create_mailbox(uint nMessages, uint nDataSize)
{
    // TODO
    return NULL;
}

i32 no_messages(mailbox* mBox)
{
    // TODO
    return 0;
}

exception send_wait(mailbox* mBox, void* pData)
{
    // TODO
    return SUCCESS;
}

exception receive_wait(mailbox* mBox, void* pData)
{
    // TODO
    return SUCCESS;
}

exception send_no_wait(mailbox* mBox, void* pData)
{
    // TODO
    return SUCCESS;
}

i32 receive_no_wait(mailbox* mBox, void* pData)
{
    // TODO
    return 0;
}

// Timing
exception wait(uint nTicks)
{
    // TODO
    return 0;
}

void set_ticks(u32 no_of_ticks)
{
    // TODO
}

u32 ticks(void)
{
    // TODO
    return 0;
}

u32	deadline(void)
{
    // TODO
    return 0;
}

void set_deadline(u32 nNew)
{
    // TODO
}

//Interrupt
void isr_off(void)
{
    // TODO
}

void isr_on(void)
{
    // TODO
}


#endif
