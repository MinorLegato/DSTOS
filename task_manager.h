#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include "kernel.h"
#include "tools.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_TASKS (2048)

enum Task_types {
    Task_waiting,
    Task_ready,
    Task_running
};


STRUCT(Task) {
    u32     type;
    TCB     tcb;
};

#define IS_TASK(task, TYPE)     (task->type == Task_##TYPE)

typedef ARRAY(Task, MAX_TASKS)  TaskList;

STRUCT(TaskManager) {
    TaskList    tasks;
    int     used;
    int     inUse[MAX_TASKS];
    TCB     tcb[MAX_TASKS];

    int     readySize;
    TCB*    readyList[MAX_TASKS];
};

// init task manager
static void initTaskManager(TaskManager* m) {
    memset(m, 0, sizeof *m);
}

// add task!  returns index to new task!
static int newTask(TaskManager* m) {
    if (m->used == MAX_TASKS) return NULL;
    m->inUse[m->used] = 1;
    int taskIndex = m->used;
    // find next empty slot for next task!
    for (; !m->inUse[m->used] && m->used < MAX_TASKS; m->used++);
    return taskIndex;
}

// remove a task!
static void deleteTask(TaskManager* m, int taskIndex) {
    m->inUse[taskIndex] = 0;
    memset(&m->tcb[taskIndex], 0, sizeof m->tcb[taskIndex]);
    m->used = taskIndex;
}

static inline TCB* getTCB(TaskManager* m, int taskIndex) {
    return &m->tcb[taskIndex];
}

// get index of task with lowest deadline!
static inline int getDeadline(TaskManager* m, int taskIndex) {
    return m->tcb[taskIndex].DeadLine;
}

static int taskCmp(const void* a, const void* b) {
    const TCB* aa = (const TCB*)a;
    const TCB* bb = (const TCB*)b;
    return aa->DeadLine < bb->DeadLine;
}

// adds task at index to readyList
// keeps the readyList sorted!
static inline void insertToReadyList(TaskManager* m, int taskIndex) {
    m->readyList[m->readySize++] = &m->tcb[taskIndex];
    qsort(m->readyList, m->readySize, sizeof *m->readyList, taskCmp);
}


#endif
