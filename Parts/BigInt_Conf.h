#ifndef __BIGINT_CONFIG__
#define __BIGINT_CONFIG__

#include <stdint.h>
#include <stdlib.h>

#define BIGINT_LEN 129
#define BIGINT_SIZE BIGINT_LEN*8
#define BIGINT_DBITS 8
#define BIGINT_BASE 256

typedef uint8_t bigint[BIGINT_LEN];
typedef int16_t ii;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;

#endif //__BIGINT_CONFIG__
