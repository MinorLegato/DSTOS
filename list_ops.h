#ifndef __LIST_OPS_H__
#define __LIST_OPS_H__

#include "kernel.h"
#include "string.h"

// =============================== TASK LIST API ===================================== //

// from kernel.h
typedef list    TaskList;
typedef listobj TaskNode;

// ================================ TASK LIST IMPLEMENTATION ======================== //

static TaskNode* allocTask(void (*body)(), u32 d) {
    TaskNode* task = NULL;
    TCB*      tcb  = NULL;
    if (task = calloc(1, sizeof *task), !task) { return NULL; }
    if (tcb  = calloc(1, sizeof *task), !tcb)  { free(task); return NULL; }
    tcb->DeadLine = d;
    tcb->PC = body;
    tcb->SP = tcb->StackSeg;
    task->pTask = tcb;
    return task;
}

static void initTaskList(TaskList* taskList) {
    taskList->pHead = NULL;
    taskList->pTail = NULL;
}

static int noTasks(TaskList* taskList) {
    return taskList->pHead == taskList->pTail;
}

static void insertTask(TaskNode* newNode, TaskNode* prev, TaskNode* next) {
    next->pPrevious = newNode;
    newNode->pNext = next;
    newNode->pPrevious = prev;
    prev->pNext = newNode;
}

static void addTask(TaskList* taskList, TaskNode* newNode) {
    if (!newNode) { return; }
    if (taskList->pHead == NULL) {
        taskList->pHead = newNode;
        taskList->pTail = newNode;
    } else {
        insertTask(newNode, taskList->pHead, taskList->pHead->pNext);
    }
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

