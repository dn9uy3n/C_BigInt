#ifndef __BIGINT_SET__
#define __BIGINT_SET__

#include "BigInt_Conf.h"
#include <string.h>

// a = 0
void bigint_set_zero(bigint a)
{
    memset(a, 0, BIGINT_LEN);
}
// a = b
void bigint_set_int(uin b, bigint a)
{
    
    for (ii i=0; i<BIGINT_LEN; i++)
    {
        a[i] = b % BIGINT_BASE;
        b /= BIGINT_BASE;
    }
}
// a = b
void bigint_set_bigint(bigint b, bigint a)
{
    memcpy(a, b, BIGINT_LEN);
}

#endif
