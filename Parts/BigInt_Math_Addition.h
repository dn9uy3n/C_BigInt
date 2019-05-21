#ifndef __BIGINT_MATH_ADDITION__
#define __BIGINT_MATH_ADDITION__

#include "BigInt_Conf.h"
#include "BigInt_Set.h"
#include "BigInt_Comp.h"

// res = gcd(a,b) // &res != &a != &b
void bigint_gcd(bigint a, bigint b, bigint res)
{
    if (bigint_is_equal_int(0,a) || bigint_is_equal_int(0,b))
    {
        bigint_set_zero(res);
        return;
    }

    bigint _a,_b,t;
    bigint_set_bigint(a,_a);
    bigint_set_bigint(b,_b);

    while (!bigint_is_equal_int(0,_b))
    {
        bigint_set_bigint(_b,t);
        bigint_mod_bigint_res(t,_a,_b);
        bigint_set_bigint(t,_a);
    }
    bigint_set_bigint(_a,res);
}
// res = gcd(a,b), a*x + b*y = res // &res != &a != &b != &x != &y
void bigint_gcd_extend(bigint a, bigint b, bigint res, bigint x, bigint y)
{
    if (bigint_is_equal_int(0,b))
    {
        bigint_set_bigint(a,res);
        bigint_set_int(1,x);
        bigint_set_zero(y);
        return;
    }
    bigint _a,_b,_x,t;

    bigint_set_bigint(b,_a);
    bigint_mod_bigint_res(b,a,_b);
    bigint_gcd_extend(_a, _b, res, _x, x);

    bigint_set_bigint(a,t);
    bigint_div_bigint(b,t);
    bigint_mul_bigint(x,t);
    bigint_sub_bigint_res(t,_x,y);
}
#endif
