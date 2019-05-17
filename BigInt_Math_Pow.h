#ifndef __BIGINT_MATH_POW__
#define __BIGINT_MATH_POW__

#include "BigInt_Conf.h"
#include "BigInt_Comp.h"
#include "BigInt_Bits.h"
#include "BigInt_Math_Base.h"
#include "BigInt_Math_Log.h"
#include "BigInt_Math_Mul.h"
#include "BigInt_Bits.h"



// d = a^b mod c
void bigint_pow_mod_bigint(bigint a, bigint b, bigint c, bigint d)
{
    bigint t, _a, _b;

    bigint_set_bigint(a,_a);
    bigint_set_bigint(b,_b);
    bigint_set_zero(t);
    bigint_set_int(1,d);

    while (!bigint_equal_int(0,_b))
    {
        if (bigint_is_odd(_b))
        {
            bigint_mul_bigint_res(_a, d, t);
            bigint_mod_bigint_res(c, t, d);
        }
        bigint_shift_bit_right(_b, 1);
        bigint_set_bigint(_a,t);
        bigint_mul_bigint(_a, t);
        bigint_mod_bigint_res(c, t, _a);
    }
}
#endif
