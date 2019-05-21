#ifndef __BIGINT_COMP__
#define __BIGINT_COMP__

#include "BigInt_Conf.h"
#include "BigInt_Set.h"
#include "BigInt_Bits.h"
#include "bool.h"

// a == b
bool bigint_equal_bigint(bigint b, bigint a)
{
    for (ii i=0; i<BIGINT_LEN; i++)
        if (a[i] != b[i])
            return false;
    return true;
}
// a == b
bool bigint_equal_int(uin b, bigint a)
{
    bigint _b; bigint_set_int(b, _b);
    return bigint_equal_bigint(_b,a);
}
bool bigint_less_bigint(bigint a, bigint b)
{
    for (ii i = BIGINT_LEN - 1; i>=0; i--)
    {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return false;
}
// a <= b
bool bigint_less_equal_bigint(bigint a, bigint b)
{
    for (ii i = BIGINT_LEN - 1; i>=0; i--)
    {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return true;
}
// a <= b
bool bigint_less_equal_int(uin a, bigint b)
{
    bigint _a; bigint_set_int(a,_a);
    return bigint_less_equal_bigint(_a,b);
}
// a % 2 == 0
bool bigint_is_even(bigint a)
{
    return !(a[0]&1);
}
// a % 2 == 1
bool bigint_is_odd(bigint a)
{
    return (a[0]&1);
}
// return (a<0)
bool bigint_is_negative(bigint a)
{
    return (bigint_is_on_bit(a,BIGINT_SIZE-1));
}
bool bigint_is_positive(bigint a)
{
    return !(bigint_is_on_bit(a, BIGINT_SIZE-1));
}
#endif
