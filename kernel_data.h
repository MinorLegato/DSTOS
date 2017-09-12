#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__

#include "kernel.h"
#include "tools.h"

i32 kernelMode  = 0;
// from kernel.h
i32 tickCounter = 0;

#include "tasks.h"

void TimerInt(void) {
    tickCounter++;

    TaskNode* iter = getFirstTask(timerList);

    while (iter != getDummyTask(timerList) && getnTCnt(iter) <= ticks()) {
        addTask_Deadline(readyList, removeNode(iter));
        iter = getFirstTask(timerList);
    }

    iter = getFirstTask(waitList);

    while (iter != getDummyTask(waitList) && getDeadline(iter) <= ticks()) {
        addTask_Deadline(readyList, removeNode(iter));
        iter = getFirstTask(waitList);
    }
}

void idleTask() { while (1) { SaveContext(); TimerInt(); LoadContext(); } }

#endif

