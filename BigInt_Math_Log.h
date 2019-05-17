#ifndef __BIGINT_MATH_LOG__
#define __BIGINT_MATH_LOG__

#include "BigInt_Conf.h"
#include "BigInt_Bits.h"

// return log2(a)
uin bigint_log2(bigint a)
{
    for (ii i=BIGINT_LEN-1; i>=0; i--)
        if (a[i]!=0)
            for (ii j=7; j>=0; j--)
                if (a[i]&(1<<j))
                    return j+i*8;
    return 0;
}
#endif
