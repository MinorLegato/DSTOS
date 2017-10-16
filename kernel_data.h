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
        addTask_nTCnt(readyList, removeTask(iter));
        iter = getFirstTask(timerList);
    }

    iter = getFirstTask(waitList);

    while (iter != getDummyTask(waitList) && getDeadline(iter) <= ticks()) {
        addTask_Deadline(readyList, removeTask(iter));
        iter = getFirstTask(waitList);
    }

    Running = getFirstTask(readyList)->pTask;
}

void idleTask() { while (1) { SaveContext(); TimerInt(); LoadContext(); } }

void isr_off() {}
void isr_on()  {}

#endif

