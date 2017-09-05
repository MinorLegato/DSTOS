#ifndef __KERNEL_DATA_H__
#define __KERNEL_DATA_H__

#include "kernel.h"
#include "tools.h"

i32 kernelMode  = 0;
// from kernel.h
i32 tickCounter = 0;
//
void idleTask() { while (1); }

#include "tasks.h"

#endif

