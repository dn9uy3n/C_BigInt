#ifndef __BIGINT_MATH_BASE__
#define __BIGINT_MATH_BASE__

#include "BigInt_Conf.h"
#include "BigInt_Set.h"

// a += b
void bigint_add_bigint(bigint b, bigint a)
{
    uin x= 0;
    for (ii i=0; i< BIGINT_LEN; i++)
    {
        x += b[i];
        x += a[i];
        a[i] = x % BIGINT_BASE;
        x /= BIGINT_BASE;
    }
}
// res = a + b // &res != {a,b}
void bigint_add_bigint_res(bigint b, bigint a, bigint res)
{
    bigint_set_bigint(a,res);
    bigint_add_bigint(b,res);
}
// a += b
void bigint_add_int(uin b, bigint a)
{
    uin x = b;
    for (ii i = 0; i < BIGINT_LEN; i++)
    {
        x += a[i];
        a[i] = x % BIGINT_BASE;
        x /= BIGINT_BASE;
    }
}
// res = a + b // &res != {a}
void bigint_add_int_res(uin b, bigint a, bigint res)
{
    bigint_set_bigint(a,res);
    bigint_add_int(b,res);
}
// a -= b
void bigint_sub_bigint(bigint b, bigint a)
{
    uin r = 0;
    for (ii i = 0; i < BIGINT_LEN; i++)
        if (a[i] < r + b[i])
        {
            a[i] = BIGINT_BASE - b[i] - r + a[i];
            r = 1;
        }
        else
        {
            a[i] -= r + b[i];
            r = 0;
        }
}
// res = a - b // &res != {a,b}
void bigint_sub_bigint_res(bigint b, bigint a, bigint res)
{
    bigint_set_bigint(a,res);
    bigint_sub_bigint(b,res);
}
// a -= b
void bigint_sub_int(uin b, bigint a)
{
    uin r = b;
    for (ii i = 0; i < BIGINT_LEN; i++)
        if (a[i] < r % BIGINT_BASE)
        {
            a[i] = BIGINT_BASE - r % BIGINT_BASE + a[i];
            r = r / BIGINT_BASE + 1;
        }
        else
        {
            a[i] -= r % BIGINT_BASE;
            r /= BIGINT_BASE;
        }
}
// res = a - b // &res != {a}
void bigint_sub_int_res(uin b, bigint a, bigint res)
{
    bigint_set_bigint(a,res);
    bigint_sub_int(b,res);
}
#endif
