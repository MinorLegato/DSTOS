#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include "kernel.h"
#include "tools.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAX_TASKS (2048)

enum Task_types {
    Task_none,
    Task_waiting,
    Task_ready,
    Task_running,
    Task_count
};

STRUCT(Task) {
    u32     type;
    TCB     tcb;
};

#define TASK(task, TYPE) (task->type == Task_##TYPE)

static u32 getDeadline(const Task* task) {
    return task->tcb.DeadLine;
}

typedef ARRAY(i32, MAX_TASKS) TaskList;

#endif
