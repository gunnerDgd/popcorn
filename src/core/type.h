#ifndef CORE_TYPE_H
#define CORE_TYPE_H

#ifdef PRESET_LINUX
#include <linux/types.h>
#include <linux/stddef.h>
#include <linux/stdarg.h>

typedef uint8_t  u8_t ;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef uint64_t u64_t;

typedef int8_t   i8_t ;
typedef int16_t  i16_t;
typedef int32_t  i32_t;
typedef int64_t  i64_t;

typedef float    f32_t;
typedef double   f64_t;

typedef bool     bool_t;
typedef void*    any_t ;
#endif

#define false_t  0
#define true_t   1
#define null_t  ((void*)0)

typedef u64_t u128_t[2];
typedef i64_t i128_t[2];

typedef u64_t u256_t[4];
typedef i64_t i256_t[4];

#if PRESET_ARCH_BIT == 64
typedef u64_t reg_t;
#endif

#if PRESET_ARCH_BIT == 32
typedef u32_t reg_t;
#endif

#endif
