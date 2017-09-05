#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__

#include "kernel.h"
#include "tools.h"

i32 kernelMode  = 0;
// from kernel.h
i32 tickCounter = 0;
//

void TimerInt(void) { tickCounter++; }
void idleTask() { while (1) { SaveContext(); TimerInt(); LoadContext(); } }

#include "tasks.h"

#endif

