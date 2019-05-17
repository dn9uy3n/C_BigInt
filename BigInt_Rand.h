#ifndef __BIGINT_RAND__
#define __BIGINT_RAND__

#include "LargeInt_Conf.h"
#include "LargeInt_Math.h"
#include <time.h>

// a = rand()
void bigint_rand(bigint a)
{
    srand(time(NULL));
    for (ii i=0; i<BIGINT_LEN; i++)
        a[i] = rand() % BIGINT_BASE;
}
// a = rand() % lim
void bigint_rand_range(bigint a, bigint lim)
{
    bigint_rand(a);
    bigint_div_bigint(lim,a);
}

#endif
