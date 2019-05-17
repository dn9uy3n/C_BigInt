#ifndef __BIGINT_RAND__
#define __BIGINT_RAND__

#include "BigInt_Conf.h"
#include "BigInt_Math.h"
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
    bigint_mod_bigint(lim,a);
}

#endif
