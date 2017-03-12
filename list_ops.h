#ifndef __LIST_OPS_H__
#define __LIST_OPS_H__

#include "kernel.h"
#include "string.h"

// ==================================== TASK LIST API ========================================== //

// from kernel.h
//typedef list    TaskList;
//typedef listobj TaskNode;


typedef struct Task {
    int     inUse;
    TBC     task;
} Task;


typedef struct TaskList {
    Task*   tasks;
    uint    size;
} TaskList;


// ==================================== TASK LIST IMPLEMENTATION ============================= //

static initTaskList(TaskList* taskList, int maxTasks)
{
    taskList->tasks = calloc(maxTasks, sizeof *taskList->tasks);
    taskList->size = maxTasks;
}


static Task* findEmptyTask(TaskList* taskList)
{
    int i = 0;
    while (i < taskList->size && taskList->tasks[i].inUse) i++;

    Task* task = &taskList->tasks[i];

    if (!task->inUse) { task->inUse = 1; return task; }

    return NULL;
}



static int newTask(TaskList* taskList, void(*body)(), uint d)
{
    Task* task = findEmptyTask(taskList);

    if (!task) return 0;


    return 1;
}


/*
static void initTaskList(TaskList* taskList)
{
    taskList->pHead = NULL;
    taskList->pTail = NULL;
}

static int noTasks(TaskList* taskList)
{
    return taskList->pHead == taskList->pTail;
}

static void insertTask(TaskNode* newNode, TaskNode* prev, TaskNode* next)
{
    next->pPrevious = newNode;
    newNode->pNext = next;
    newNode->pPrevious = prev;
    prev->pNext = newNode;
}

static void addTask(TaskList* taskList, TaskNode* newNode)
{
    if (taskList->pHead == NULL) {
        taskList->pHead = newNode;
        taskList->pTail = newNode;
    } else {
        insertTask(newNode, taskList->pHead, taskList->pHead->pNext);
    }

    //TaskNode* iter = head->pNext;
    //while (iter != head && taskDeadline(newNode) < taskDeadline(iter))
        //iter = iter->pNext;
    //insertTask(newNode, iter->pPrevious, iter);
}

static void clearTasks(TaskList* head)
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
*/
#endif

