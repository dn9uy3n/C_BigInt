#ifndef __BIGINT_MATH_MUL__
#define __BIGINT_MATH_MUL__

#include "BigInt_Conf.h"
#include "BigInt_Comp.h"
#include "BigInt_Bits.h"
#include "BigInt_Math_Base.h"
#include "BigInt_Math_Log.h"
#include "BigInt_Bits.h"

// a *= b
void bigint_mul_int(uin b, bigint a)
{
    uin r = 0;
    for (ii i = 0; i < BIGINT_LEN; i++)
    {
        r += (uin)b * a[i];
        a[i] = r % BIGINT_BASE;
        r /= BIGINT_BASE;
    }
}
// res = a * b // &res!= {&a}
void bigint_mul_int_res(uin b, bigint a, bigint res)
{
    uin r = 0;
    for (ii i=0; i< BIGINT_LEN; i++)
    {
        r += (uin)b * a[i];
        res[i] = r % BIGINT_BASE;
        r /= BIGINT_BASE;
    }
}
// a *= b // &a != &b
void bigint_mul_bigint(bigint b, bigint a)
{
    bigint t, _res;
    bigint_set_zero(_res);
    for (ii i = 0; i < BIGINT_LEN; i++)
    {
        bigint_mul_int_res(a[i], b, t);
        bigint_shift_digit_left(t, i);
        bigint_add_bigint(t, _res);
    }
    bigint_set_bigint(_res, a);
}
// res = a * b // &a != &b
void bigint_mul_bigint_res(bigint b, bigint a, bigint res)
{
    bigint t;
    bigint_set_zero(res);
    for (ii i = 0; i < BIGINT_LEN; i++)
    {
        bigint_mul_int_res(a[i], b, t);
        bigint_shift_digit_left(t, i);
        bigint_add_bigint(t, res);
    }
}
// a /= b // &a != &b
void bigint_div_bigint(bigint b, bigint a)
{
    // case: a <= b
    if (bigint_less_bigint(a,b))
    {
        bigint_set_zero(a);
        return;
    }
    if (bigint_equal_bigint(a,b))
    {
        bigint_set_int(1,a);
        return;
    }

    // case a > b
    i16 diff = (i16) bigint_log2(a) - bigint_log2(b);
    if (diff == 0)
    {
        bigint_set_int(1,a);
        return;
    }

    bigint _mul_b; // _mul_b = 2^_x*b
    bigint _2_x;
    bigint _res;

    bigint_set_zero(_res);
    bigint_set_bigint(b,_mul_b);
    bigint_shift_bit_left(_mul_b, diff);
    bigint_set_int(1,_2_x);
    bigint_shift_bit_left(_2_x, diff);

    if (bigint_less_bigint(a,_mul_b))
    {
        bigint_shift_bit_right(_mul_b,1);
        bigint_shift_bit_right(_2_x,1);
    }

    while (!bigint_less_bigint(a,b))
    {
        bigint_sub_bigint(_mul_b, a); // a -= 2^_x *b
        bigint_add_bigint(_2_x,_res); // res += 2^x

        //shift right _mul_b until binary length _mul_b = binary length a
        diff = (i16) bigint_log2(_mul_b) - bigint_log2(a);
        bigint_shift_bit_right(_mul_b,diff);
        bigint_shift_bit_right(_2_x,diff);

        if (bigint_less_bigint(a,_mul_b))
        {
            bigint_shift_bit_right(_mul_b,1);
            bigint_shift_bit_right(_2_x,1);
        }
    }
    bigint_set_bigint(_res,a);
}
// res = a / b // &res != {&a,&b}
void bigint_div_bigint_res(bigint b, bigint a, bigint res)
{
    // case: a <= b
    if (bigint_less_bigint(a,b))
    {
        bigint_set_zero(res);
        return;
    }
    if (bigint_equal_bigint(a,b))
    {
        bigint_set_int(1,res);
        return;
    }

    // case a > b
    i16 diff = (i16) bigint_log2(a) - bigint_log2(b);
    if (diff == 0)
    {
        bigint_set_int(1,res);
        return;
    }

    bigint _mul_b; // _mul_b = 2^_x*b
    bigint _2_x;
    bigint _a;

    bigint_set_bigint(a,_a);
    bigint_set_zero(res);
    bigint_set_bigint(b,_mul_b);
    bigint_shift_bit_left(_mul_b, diff);
    bigint_set_int(1,_2_x);
    bigint_shift_bit_left(_2_x, diff);

    if (bigint_less_bigint(a,_mul_b))
    {
        bigint_shift_bit_right(_mul_b,1);
        bigint_shift_bit_right(_2_x,1);
    }

    while (!bigint_less_bigint(a,b))
    {
        bigint_sub_bigint(_mul_b, a); // a -= 2^_x *b
        bigint_add_bigint(_2_x,res); // res += 2^x

        //shift right _mul_b until binary length _mul_b = binary length a
        diff = (i16) bigint_log2(_mul_b) - bigint_log2(a);
        bigint_shift_bit_right(_mul_b,diff);
        bigint_shift_bit_right(_2_x,diff);

        if (bigint_less_bigint(a,_mul_b))
        {
            bigint_shift_bit_right(_mul_b,1);
            bigint_shift_bit_right(_2_x,1);
        }
    }
    bigint_set_bigint(_a,a);
}
// a /= b // &a != &b
void bigint_div_int(uin b, bigint a)
{
    bigint _b; bigint_set_int(b,_b);
    bigint_div_bigint(_b,a);
}
// res = a / b // &res != {&a,&b}
void bigint_div_int_res(uin b, bigint a, bigint res)
{
    bigint_set_bigint(a,res);
    bigint_div_int(b,res);
}
// q = a / b, r = a % b // &a!=&b!=&c!=&d
void bigint_divide_bigint(bigint b, bigint a, bigint q, bigint r)
{
    // case: a <= b
    if (bigint_less_bigint(a,b))
    {
        bigint_set_zero(q);
        return;
    }
    if (bigint_equal_bigint(a,b))
    {
        bigint_set_int(1,q);
        return;
    }

    // case a > b
    i16 diff = (i16) bigint_log2(a) - bigint_log2(b);
    if (diff == 0)
    {
        bigint_set_int(1,q);
        return;
    }

    bigint _mul_b; // _mul_b = 2^_x*b
    bigint _2_x;
    bigint _a;

    bigint_set_bigint(a,_a);
    bigint_set_zero(q);
    bigint_set_bigint(b,_mul_b);
    bigint_shift_bit_left(_mul_b, diff);
    bigint_set_int(1,_2_x);
    bigint_shift_bit_left(_2_x, diff);

    if (bigint_less_bigint(a,_mul_b))
    {
        bigint_shift_bit_right(_mul_b,1);
        bigint_shift_bit_right(_2_x,1);
    }

    while (!bigint_less_bigint(a,b))
    {
        bigint_sub_bigint(_mul_b, a); // a -= 2^_x *b
        bigint_add_bigint(_2_x,q); // q += 2^x

        //shift right _mul_b until binary length _mul_b = binary length a
        diff = (i16) bigint_log2(_mul_b) - bigint_log2(a);
        bigint_shift_bit_right(_mul_b,diff);
        bigint_shift_bit_right(_2_x,diff);

        if (bigint_less_bigint(a,_mul_b))
        {
            bigint_shift_bit_right(_mul_b,1);
            bigint_shift_bit_right(_2_x,1);
        }
    }
    bigint_set_bigint(a,r);
    bigint_set_bigint(_a,a);
}
// a %= b
void bigint_mod_bigint(bigint b, bigint a)
{
    // case: a <= b
    if (bigint_less_bigint(a,b))
        return;
    if (bigint_equal_bigint(a,b))
    {
        bigint_set_zero(a);
        return;
    }

    // case a > b
    i16 diff = (i16) bigint_log2(a) - bigint_log2(b);
    if (diff == 0)
    {
        bigint_set_int(1,a);
        return;
    }

    bigint _mul_b; // _mul_b = 2^_x*b
    bigint _res;

    bigint_set_zero(_res);
    bigint_set_bigint(b,_mul_b);
    bigint_shift_bit_left(_mul_b, diff);

    if (bigint_less_bigint(a,_mul_b))
        bigint_shift_bit_right(_mul_b,1);

    while (!bigint_less_bigint(a,b))
    {
        bigint_sub_bigint(_mul_b, a); // a -= 2^_x *b

        //shift right _mul_b until binary length _mul_b = binary length a
        diff = (i16) bigint_log2(_mul_b) - bigint_log2(a);
        bigint_shift_bit_right(_mul_b,diff);

        if (bigint_less_bigint(a,_mul_b))
            bigint_shift_bit_right(_mul_b,1);
    }
}
// res = a % b // &res != {&a,&b}
void bigint_mod_bigint_res(bigint b, bigint a, bigint res)
{
    // case: a <= b
    if (bigint_less_bigint(a,b))
    {
        bigint_set_bigint(a,res);
        return;
    }
    if (bigint_equal_bigint(a,b))
    {
        bigint_set_zero(res);
        return;
    }

    // case a > b
    i16 diff = (i16) bigint_log2(a) - bigint_log2(b);
    if (diff == 0)
    {
        bigint_set_int(1,a);
        return;
    }

    bigint _mul_b; // _mul_b = 2^_x*b
    bigint _a;

    bigint_set_bigint(a,_a);
    bigint_set_zero(res);
    bigint_set_bigint(b,_mul_b);
    bigint_shift_bit_left(_mul_b, diff);

    if (bigint_less_bigint(a,_mul_b))
        bigint_shift_bit_right(_mul_b,1);

    while (!bigint_less_bigint(a,b))
    {
        bigint_sub_bigint(_mul_b, a); // a -= 2^_x *b

        //shift right _mul_b until binary length _mul_b = binary length a
        diff = (i16) bigint_log2(_mul_b) - bigint_log2(a);
        bigint_shift_bit_right(_mul_b,diff);

        if (bigint_less_bigint(a,_mul_b))
            bigint_shift_bit_right(_mul_b,1);
    }
    bigint_set_bigint(a,res);
    bigint_set_bigint(_a,a);
}
// return a % b
uin bigint_mod_int_res(uin b, bigint a)
{
    uin r = 0;
    for (ii i = BIGINT_LEN - 1; i>=0; i--)
        r = (r * BIGINT_BASE + a[i]) % b;
    return r;
}
// a %= b
void bigint_mod_int(uin b, bigint a)
{
    uin res = bigint_mod_int_res(b,a);
    bigint_set_int(res,a);
}

#endif
