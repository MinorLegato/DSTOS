#ifndef __LIST_OPS_H__
#define __LIST_OPS_H__

#include "kernel.h"
#include "string.h"

// ==================================== TASK LIST API ========================================== //

// from kernel.h
typedef listobj TaskList;
typedef listobj TaskNode;

#define forTasks(HEAD, ITER) \
    for ((ITER) = (HEAD)->pNext; (ITER) != (HEAD); (ITER) = (ITER)->pNext)

#define taskDeadline(NODE) ((NODE)->pTask->DeadLine)

static int initTasks(TaskList* head);
static int noTasks(TaskList* head);

static void removeTasks(TaskList* head);
static void addTask(TaskList* head, TaskNode* node);

static TaskNode* removeTask(TaskList* head, TaskNode* node);
static TaskNode* findLowestDeadline(const TaskList* head);


// ==================================== TASK LIST IMPLEMENTATION ============================= //


static int initTasks(TaskList* head)
{
    memset(head, 0, sizeof *head);

    if (head == NULL) return 0;

    head->pPrevious = head;
    head->pNext     = head;

    return 1;
}

static int noTasks(TaskList* head)
{
    return head == head->pNext;
}

static void insertTask(TaskNode* prev, TaskNode* next, TaskNode* newNode)
{
    newNode->pNext = prev->pNext;
    newNode->pPrevious = next->pPrevious;
    next->pPrevious = newNode;
    prev->pNext = newNode;
}

static void addTask(TaskList* head, TaskNode* newNode)
{
    TaskNode* iter;

    forTasks(head, iter) {
        if (taskDeadline(iter) >= taskDeadline(newNode))
            break;
    }

    insertTask(iter->pPrevious, iter->pNext, newNode);
}

static void removeTasks(TaskList* head)
{
    // TODO
}

static TaskNode* removeTask(TaskList* head, TaskNode* node)
{
    // TODO
    return NULL;
}

static TaskNode* findLowestDeadline(const TaskList* head)
{
    return 0;
}

#endif

