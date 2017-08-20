#ifndef __LIST_OPS_H__
#define __LIST_OPS_H__

#include "kernel.h"
#include "string.h"
#include "kernel_data.h"

// =============================== TASK LIST API ===================================== //

// from kernel.h
typedef list    TaskList;
typedef listobj TaskNode;

// ================================ TASK LIST IMPLEMENTATION ======================== //

static TaskNode* allocTask(void (*body)(), u32 d) {
    TaskNode* task = NULL;
    TCB*      tcb  = NULL;
    if (task = alloc(sizeof *task), !task) { return NULL; }
    if (tcb  = alloc(sizeof *task), !tcb)  { free(task); return NULL; }
    tcb->DeadLine = d;
    tcb->PC = body;
    tcb->SP = tcb->StackSeg;
    task->pTask = tcb;
    return task;
}

static void initTaskList(TaskList* taskList) {
    taskList->pHead = alloc(sizeof (TaskNode));
    taskList->pTail = alloc(sizeof (TaskNode));
    taskList->pHead->pNext = taskList->pTail;
    taskList->pTail->pPrevious = taskList->pHead;
}

static int noTasks(TaskList* taskList) {
    return taskList->pHead->pNext == taskList->pTail;
}

static void insertTask(TaskNode* newNode, TaskNode* prev, TaskNode* next) {
    next->pPrevious = newNode;
    newNode->pNext = next;
    newNode->pPrevious = prev;
    prev->pNext = newNode;
}

static void addTask_Deadline(TaskList* taskList, TaskNode* newNode){
    if (!newNode) { return; }
    TaskNode* temp = taskList->pHead;
    while (temp->pNext != taskList->pTail
           && newNode->pTask->DeadLine > temp->pNext->pTask->DeadLine){
        temp = temp->pNext;
    }
    insertTask(newNode, temp, temp->pNext);
}

static void addTask_nTCnt(TaskList* taskList, TaskNode* newNode) {
    if (!newNode) { return; }
    
}

static void clearTasks(TaskList* head) {
    // TODO
}

static TaskNode* removeTask(TaskNode* node) {
    node->pPrevious->pNext = node->pNext;
    node->pNext->pPrevious = node->pPrevious;
    return node;
}

static TaskNode* findLowestDeadline(const TaskList* head) {
    return 0;
}

#endif

