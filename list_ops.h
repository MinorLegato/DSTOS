#ifndef __LIST_OPS_H__
#define __LIST_OPS_H__

#include "kernel.h"
#include "string.h"

// ==================================== TASK LIST API ========================================== //

// from kernel.h
typedef list    TaskList;
typedef listobj TaskNode;

// ==================================== TASK LIST IMPLEMENTATION ============================= //

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

static TaskNode* removeTask(TaskList* head, TaskNode* node) {
    // TODO
    return NULL;
}

static TaskNode* findLowestDeadline(const TaskList* head) {
    return 0;
}

#endif

