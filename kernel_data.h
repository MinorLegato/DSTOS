#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__

#include "kernel.h"
#include "tools.h"

typedef list    TaskList;
typedef listobj TaskNode;

// ================================= TYPES/DATA =================================== //

extern i32 kernelMode;
extern i32 tickCounter;

extern TaskList*   timerList;
extern TaskList*   waitList;
extern TaskList*   readyList;
extern TCB*        Running;

// ====================================== TASKS API  ====================================== //

TCB*    getTCB      (const TaskNode* const task);
uint    getDeadline (const TaskNode* const task);
uint    getnTCnt    (const TaskNode* const task);
msg*    getTaskMsg  (const TaskNode* const task);

TaskNode*   getNextTask (const TaskNode* const task);
TaskNode*   getPrevTask (const TaskNode* const task);
TaskNode*   allocTask   (void (*body)(), uint d);

void        deleteTask(TaskNode* tasks);
void        insertTask(TaskNode* const new, TaskNode* const prev, TaskNode* const next);
TaskNode*   removeTask(TaskNode* const task);

TaskNode*   getDummyTask    (const TaskList* const tasks);
TaskNode*   getFirstTask    (const TaskList* const tasks);
TaskNode*   getLastTask     (const TaskList* const tasks);

TaskList*   allocTaskList();

int     noTasks             (const TaskList* const tasks);
void    addTask_Deadline    (TaskList* const tasks, TaskNode* const new);
void    addTask_nTCnt       (TaskList* const tasks, TaskNode* const new);
void    printTaskList       (const TaskList* const tasks);

// ================================== MESSAGES API ========================================= //

msg*        nextMsg         (const msg* const node);
msg*        prevMsg         (const msg* const node);
TaskNode*   getTask         (const msg* const m);
void*       getData         (const msg* const m);

b32         setMessage      (msg* const m, const void* const data, i32 size);
msg*        createMsg       (void* data, i32 size);
void        deleteMsg       (msg* m);

i32         getDataSize     (const mailbox* const mBox);
i32         getMsgMax       (const mailbox* const mBox);
i32         getMsgCount     (const mailbox* const mBox);

msg*        getFirstMsg     (const mailbox* const mBox);
msg*        getLastMsg      (const mailbox* const mBox);
msg*        getDummyMsg     (const mailbox* const mBox);

void        insertMsg       (msg* const new, msg* const prev, msg* const next);
msg*        removeMsg       (msg* const m);
b32         isFull          (mailbox* const mBox);
b32         msgPushFront    (mailbox* const mBox, msg* const m);
b32         msgPushBack     (mailbox* const mBox, msg* const m);
msg*        msgPopFront     (mailbox* const mBox);
msg*        msgPopBack      (mailbox* const mBox);

b32         msgRecIsWaiting (const mailbox* mBox);
b32         msgSndIsWaiting (const mailbox* mBox);

// ============================================================================================ //

void TimerInt(void);

#endif

