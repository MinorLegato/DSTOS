#ifndef __DEFS_H__
#define __DEFS_H__

#include <stdint.h>
#include <string.h>
#include <>

#define STRUCT(NAME) typedef struct NAME NAME; struct NAME

// real
typedef float r32;
typedef double r64;
// signed
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
// unsigned
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#endif
