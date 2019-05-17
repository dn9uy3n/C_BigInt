#ifndef __BIGINT_CONFIG__
#define __BIGINT_CONFIG__

#include <stdint.h>
#include <stdlib.h>

#define BIGINT_SIZE 1024
#define BIGINT_LEN 128
#define BIGINT_DBITS 8
#define BIGINT_BASE 256

typedef uint8_t bigint[BIGINT_LEN];
typedef int16_t ii;
typedef int16_t i16;
typedef uint16_t uin;

#endif //__BIGINT_CONFIG__
