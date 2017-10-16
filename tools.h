#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

typedef uint32_t    b32;

typedef float       r32;
typedef double      r64;

typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;

typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;

#define STRUCT(name) typedef struct name name; struct name

// ===================================================================================================== //

static i32 memoryCounter = 0;

static void* alloc(size_t size) {
    isr_off();
    void* data = calloc(1, size);
    if (data != NULL) { memoryCounter++; }
    isr_on();
    return data;
}

static void delete(void* data) {
    if (data) {
        isr_off();
        free(data);
        memoryCounter--;
        isr_on();
    }
}

#endif
