#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef uint8_t u8;
typedef int8_t i8;

typedef uint16_t u16;
typedef int16_t i16;

typedef uint32_t u32;
typedef int32_t i32;

typedef uint64_t u64;
typedef int64_t i64;

static inline u8 log2(u16 v)
{
	u8 r = 0;
	while (v >>= 1)
		r++;

	return r;
}

#endif
