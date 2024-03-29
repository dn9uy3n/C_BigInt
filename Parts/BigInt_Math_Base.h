#ifndef __BIGINT_MATH_BASE__
#define __BIGINT_MATH_BASE__

#include "BigInt_Conf.h"
#include "BigInt_Set.h"

// a += b
void bigint_add_bigint(bigint b, bigint a)
{
    i16 x= 0;
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
void bigint_add_int(i16 b, bigint a)
{
    i16 x = b;
    for (ii i = 0; i < BIGINT_LEN; i++)
    {
        x += a[i];
        a[i] = x % BIGINT_BASE;
        x /= BIGINT_BASE;
    }
}
// res = a + b // &res != {a}
void bigint_add_int_res(i16 b, bigint a, bigint res)
{
    bigint_set_bigint(a,res);
    bigint_add_int(b,res);
}
// a -= b
void bigint_sub_bigint(bigint b, bigint a)
{
    i16 r = 0;
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
void bigint_sub_int(i16 b, bigint a)
{
    i16 r = b;
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
void bigint_sub_int_res(i16 b, bigint a, bigint res)
{
    bigint_set_bigint(a,res);
    bigint_sub_int(b,res);
}
// a = -a
void bigint_opposite(bigint a)
{
    bigint_reverse_bit(a);
    bigint_add_int(1,a);
}
// a = abs(a)
void bigint_absolute(bigint a)
{
    if (bigint_is_negative(a))
        bigint_opposite(a);
}
#endif
