#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include "kernel.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define maxTasks (2048)

typedef struct TaskManager {
    int     next;
    int     inUse[maxTasks];
    TCB     tcb[maxTasks];

    int     readySize;
    TCB*    readyList[maxTasks];
} TaskManager;

// init task manager
static void initTaskManager(TaskManager* m) {
    memset(m, 0, sizeof *m);
}

// add task!  returns index to new task!
static int newTask(TaskManager* m) {
    if (m->next == maxTasks) return NULL;
    m->inUse[m->next] = 1;
    int taskIndex = m->next;
    // find next empty slot for next task!
    for (; !m->inUse[m->next] && m->next < maxTasks; m->next++);
    return taskIndex;
}

// remove a task!
static void deleteTask(TaskManager* m, int taskIndex) {
    m->inUse[taskIndex] = 0;
    memset(&m->tcb[taskIndex], 0, sizeof m->tcb[taskIndex]);
    m->next = taskIndex;
}

static inline TCB* getTCB(TaskManager* m, int taskIndex) {
    return &m->tcb[taskIndex];
}

// get index of task with lowest deadline!
static inline int getDeadline(TaskManager* m, int taskIndex) {
    return m->tcb[taskIndex].DeadLine;
}

static int deadlineCmp(const void* a, const void* b) {
    const TCB* aa = (const TCB*)a;
    const TCB* bb = (const TCB*)b;
    return aa->DeadLine < bb->DeadLine;
}

// adds task at index to readyList
// keeps the readyList sorted!
static inline void insertToReadyList(TaskManager* m, int taskIndex) {
    m->readyList[m->readySize++] = &m->tcb[taskIndex];
    qsort(m->readyList, m->readySize, sizeof *m->readyList, deadlineCmp);
}


#endif
