#ifndef __LIST_OPS_H__
#define __LIST_OPS_H__

#include "kernel.h"
#include "string.h"

// =============================== TASK LIST API ===================================== //

// from kernel.h
typedef list    TaskList;
typedef listobj TaskNode;

// ================================ TASK NODE FUNCTIONS ======================= //

static inline TCB* getTCB       (const TaskNode* const task)    { return task->pTask; }
static inline uint getDeadline  (const TaskNode* const task)    { return getTCB(task)->DeadLine; }
static inline uint getnTCnt     (const TaskNode* const task)    { return task->nTCnt; }
static inline msg* getTaskMsg   (const TaskNode* const task)    { return task->pMessage; }

static inline TaskNode* getNextTask(const TaskNode* const task) { return task->pNext; }
static inline TaskNode* getPrevTask(const TaskNode* const task) { return task->pPrevious; }

static TaskNode* allocTask(void (*body)(), uint d) {
    TaskNode* task = NULL;
    TCB*      tcb  = NULL;

    if (task = alloc(sizeof *task), !task)  { return NULL; }
    if (tcb  = alloc(sizeof *tcb),  !tcb)   { free(task); return NULL; }

    tcb->DeadLine   = d;
    tcb->PC         = body;
    tcb->SP         = tcb->StackSeg;

    task->pTask = tcb;

    return task;
}

static void insertTask(TaskNode* const new, TaskNode* const prev, TaskNode* const next) {
    next->pPrevious = new;
    new->pNext      = next;
    new->pPrevious  = prev;
    prev->pNext     = new;
}

static TaskNode* removeTask(TaskNode* const task) {
    TaskNode* p  = task->pPrevious;
    TaskNode* n  = task->pNext;
    p->pNext     = n;
    n->pPrevious = p;
    return task;
}

// ================================ TASK LIST FUNCTIONS ======================== //

static inline TaskNode* getDummyTask (const TaskList* const tasks) { return tasks->pHead; }
static inline TaskNode* getFirstTask (const TaskList* const tasks) { return getDummyTask(tasks)->pNext; }
static inline TaskNode* getLastTask  (const TaskList* const tasks) { return getDummyTask(tasks)->pPrevious; }

static TaskList* allocTaskList() {
    TaskList* taskList  = NULL;
    TaskNode* dummy     = NULL;

    if (taskList = alloc(sizeof *taskList), !taskList)  { return NULL; }
    if (dummy    = alloc(sizeof *dummy), !dummy)        { delete(taskList); return NULL; }

    dummy->pNext        = dummy;
    dummy->pPrevious    = dummy;
    taskList->pHead     = dummy;
    taskList->pTail     = dummy;

    return taskList;
}

static b32 initTaskList(TaskList* taskList) {
    TaskNode* dummy = alloc(sizeof *dummy);
    if (dummy == NULL) { return 0; }
    
    taskList->pHead = NULL;
    taskList->pTail = NULL;
    
    return 1;
}

static int noTasks(TaskList* taskList) {
    return taskList->pHead == taskList->pTail;
}

static void addTask_First(TaskList* taskList, TaskNode* newNode) {
    if (!newNode) { return; }
}

static void addTask_Deadline(TaskList* tasks, TaskNode* new) {
    if (!new) { return; }
    TaskNode* iter = getFirstTask(tasks);

    while (iter != getDummyTask(tasks) && getDeadline(new) > getDeadline(iter)) {
        iter = getNextTask(iter);
    }

    insertTask(new, getPrevTask(iter), iter);
}

static void addTask_nTCnt(TaskList* taskList, TaskNode* newNode) {
    if (!newNode) { return; }
    TaskNode* iter;
    forEach(iter, taskList) {
        if(iter->nTCnt > newNode->nTCnt) {
            break;
        }
    }
    insertNode(newNode, prevNode(iter), iter);
}

static void printTaskList(const TaskList* const tasks) {
    TaskNode* iter = getFirstTask(tasks);

    while (iter != getDummyTask(tasks)) {
        printf("%d\n", getDeadline(iter));
        iter = getNextTask(iter);
    }
}

#endif
