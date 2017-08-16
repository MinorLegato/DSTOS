#ifndef __TOOLS_H__
#define __TOOLS_H__

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

#define ARRAY(TYPE, SIZE) struct { i32 size; TYPE data[SIZE]; }

// get size
#define SIZE(A)         (A)->size
// push element at end of array!
#define PUSH(A, E)      { (A)->data[(A)->size++] = (E); }
// unordered remove of element at index I
#define REM(A, I)       { (A)->data[(I)] = (A)->data[--(A)->size]; }
// get element at I
#define GET(A, I)       &(A)->data[(I)]
// insert element E at I
#define INSERT(A, E, I) { memmove(GET((A), (I) + 1), GET((A), (I)), (((A)->size++) - (I)) * (sizeof (A)->data[0])); (A)->data[(I)] = (E); }
// remove element! keeps the order of elements
#define OREM(A, I)      { memmove(GET((A), (I)), GET((A), (I) + 1), (((A)->size--) - (I)) * (sizeof (A)->data[0])); }
// move element in array (D = dest, S = source)
#define MOVE(A, D, S)   { b32 b = D < S; i32 s = SIZE(A); (A)->data[s] = (A)->data[(S)]; OREM(A, S); INSERT(A, (A)->data[s], (D)); }


void* alloc(size_t size) {
    isr_off();
    void* data = calloc(1, size);
    isr_on();
    return data;
}

void delete(void* data) {
    isr_off();
    free(data);
    isr_on();
}

#endif
