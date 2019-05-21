#ifndef __BIGINT_MATH_MUL__
#define __BIGINT_MATH_MUL__

#include "BigInt_Conf.h"
#include "BigInt_Comp.h"
#include "BigInt_Bits.h"
#include "BigInt_Math_Base.h"
#include "BigInt_Math_Log.h"
#include "BigInt_Bits.h"

// a *= b
void bigint_mul_int(i16 b, bigint a)
{
    i32 r = 0, _b = b;
    for (ii i = 0; i < BIGINT_LEN; i++)
    {
        r += _b * a[i];
        a[i] = r % BIGINT_BASE;
        r /= BIGINT_BASE;
    }
}
// res = a * b // &res != &a != &b
void bigint_mul_int_res(i16 b, bigint a, bigint res)
{
    i32 r = 0, _b = b;
    for (ii i=0; i< BIGINT_LEN; i++)
    {
        r += _b * a[i];
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
// res = a * b // &res != &a != &b
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
// q = a / b; r = a % b // &a != &b != &q != &r // -abs(b) < r < abs(b)
void bigint_divide_bigint(bigint b, bigint a, bigint q, bigint r)
{
    if (bigint_is_equal_int(0,b))
    {
        bigint_set_zero(q);
        bigint_set_zero(r);
        return;
    }

    bool _positive_a = bigint_is_positive(a);
    bool _positive_b = bigint_is_positive(b);
    bool opposite = _positive_a ^ _positive_b;
    bigint_set_bigint(b,q);
    bigint_set_bigint(a,r);
    bigint_absolute(q); // abs(b)
    bigint_absolute(r); // abs(a)

    // abs(a)<abs(b)
    if (bigint_is_less_bigint(r,q))
    {
        bigint_set_zero(q);
        bigint_set_bigint(a,r);
        return;
    }
    // log2(abs(a)) == log2(abs(b))  <=>  b < a < 2*b
    if (bigint_log2(r) == bigint_log2(q))
    {
        bigint_sub_bigint(q,r);
        bigint_set_int(1,q);
    }
    // abs(a) >= 2*abs(b)
    else
    {
        bigint _b;
        bigint_set_bigint(q,_b);

        bigint _mul_b; // _mul_b = 2^x * abs(b)
        bigint _2_x; // 2^x
        i16 diff = bigint_log2(r) - bigint_log2(q);

        bigint_set_bigint(_b,_mul_b);
        bigint_shift_bit_left(_mul_b, diff);
        bigint_set_int(1,_2_x);
        bigint_shift_bit_left(_2_x, diff);

        if (bigint_is_less_bigint(r,_mul_b))
        {
            bigint_shift_bit_right(_mul_b,1);
            bigint_shift_bit_right(_2_x,1);
        }

        bigint_set_zero(q);
        while (!bigint_is_less_bigint(r,_b)) // r > 2^x * abs(b)
        {
            bigint_sub_bigint(_mul_b, r); // r -= 2^_x *b
            bigint_add_bigint(_2_x,q); // q += 2^x

            //shift right _mul_b until binary length _mul_b = binary length r
            diff = bigint_log2(_mul_b) - bigint_log2(r);
            bigint_shift_bit_right(_mul_b,diff);
            bigint_shift_bit_right(_2_x,diff);

            if (bigint_is_less_bigint(r,_mul_b))
            {
                bigint_shift_bit_right(_mul_b,1);
                bigint_shift_bit_right(_2_x,1);
            }
        }
    }

    //set sign
    if (!_positive_a)
        bigint_opposite(r);
    if (opposite)
        bigint_opposite(q);
}
// a /= b // &a != &b
void bigint_div_bigint(bigint b, bigint a)
{
    if (bigint_is_equal_int(0,b))
    {
        bigint_set_zero(a);
        return;
    }

    bool _positive_a = bigint_is_positive(a);
    bool _positive_b = bigint_is_positive(b);
    bool opposite = _positive_a ^ _positive_b;
    bigint_absolute(b); // abs(b)
    bigint_absolute(a); // abs(a)

    // abs(a)<abs(b)
    if (bigint_is_less_bigint(a,b))
    {
        bigint_set_zero(a);
        return;
    }
    // log2(abs(a)) == log2(abs(b))  <=>  b < a < 2*b
    if (bigint_log2(a) == bigint_log2(b))
    {
        bigint_set_int(1,a);
    }
    // abs(a) >= 2*abs(b)
    else
    {
        bigint r;
        bigint_set_bigint(a,r);

        bigint _mul_b; // _mul_b = 2^x * abs(b)
        bigint _2_x; // 2^x
        i16 diff = bigint_log2(r) - bigint_log2(b);

        bigint_set_bigint(b,_mul_b);
        bigint_shift_bit_left(_mul_b, diff);
        bigint_set_int(1,_2_x);
        bigint_shift_bit_left(_2_x, diff);

        if (bigint_is_less_bigint(r,_mul_b))
        {
            bigint_shift_bit_right(_mul_b,1);
            bigint_shift_bit_right(_2_x,1);
        }

        bigint_set_zero(a);
        while (!bigint_is_less_bigint(r,b)) // r > 2^x * abs(b)
        {
            bigint_sub_bigint(_mul_b, r); // r -= 2^_x *b
            bigint_add_bigint(_2_x,a); // q += 2^x

            //shift right _mul_b until binary length _mul_b = binary length r
            diff = bigint_log2(_mul_b) - bigint_log2(r);
            bigint_shift_bit_right(_mul_b,diff);
            bigint_shift_bit_right(_2_x,diff);

            if (bigint_is_less_bigint(r,_mul_b))
            {
                bigint_shift_bit_right(_mul_b,1);
                bigint_shift_bit_right(_2_x,1);
            }
        }
    }

    //restore b
    if (!_positive_b)
        bigint_opposite(b);
    //set sign
    if (opposite)
        bigint_opposite(a);
}
// res = a / b // &res != &a != &b
void bigint_div_bigint_res(bigint b, bigint a, bigint res)
{
    if (bigint_is_equal_int(0,b))
    {
        bigint_set_zero(res);
        return;
    }

    bool _positive_a = bigint_is_positive(a);
    bool _positive_b = bigint_is_positive(b);
    bool opposite = _positive_a ^ _positive_b;
    bigint_absolute(b); // abs(b)
    bigint_absolute(a); // abs(a)

    // abs(a)<abs(b)
    if (bigint_is_less_bigint(a,b))
    {
        bigint_set_zero(res);
        return;
    }
    // log2(abs(a)) == log2(abs(b))  <=>  b < a < 2*b
    if (bigint_log2(a) == bigint_log2(b))
    {
        bigint_set_int(1,res);
    }
    // abs(a) >= 2*abs(b)
    else
    {
        bigint r;
        bigint_set_bigint(a,r);

        bigint _mul_b; // _mul_b = 2^x * abs(b)
        bigint _2_x; // 2^x
        i16 diff = bigint_log2(r) - bigint_log2(b);

        bigint_set_bigint(b,_mul_b);
        bigint_shift_bit_left(_mul_b, diff);
        bigint_set_int(1,_2_x);
        bigint_shift_bit_left(_2_x, diff);

        if (bigint_is_less_bigint(r,_mul_b))
        {
            bigint_shift_bit_right(_mul_b,1);
            bigint_shift_bit_right(_2_x,1);
        }

        bigint_set_zero(res);
        while (!bigint_is_less_bigint(r,b)) // r > 2^x * abs(b)
        {
            bigint_sub_bigint(_mul_b, r); // r -= 2^_x *b
            bigint_add_bigint(_2_x,res); // q += 2^x

            //shift right _mul_b until binary length _mul_b = binary length r
            diff = bigint_log2(_mul_b) - bigint_log2(r);
            bigint_shift_bit_right(_mul_b,diff);
            bigint_shift_bit_right(_2_x,diff);

            if (bigint_is_less_bigint(r,_mul_b))
            {
                bigint_shift_bit_right(_mul_b,1);
                bigint_shift_bit_right(_2_x,1);
            }
        }
    }

    //restore b
    if (!_positive_b)
        bigint_opposite(b);
    if (!_positive_a)
        bigint_opposite(a);
    //set sign
    if (opposite)
        bigint_opposite(res);
}
// a /= b // &a != &b
void bigint_div_int(i16 b, bigint a)
{
    bigint _b; bigint_set_int(b,_b);
    bigint_div_bigint(_b,a);
}
// res = a / b // &res != &a != &b
void bigint_div_int_res(i16 b, bigint a, bigint res)
{
    bigint_set_bigint(a,res);
    bigint_div_int(b,res);
}
// a %= b // &a != &b
void bigint_mod_bigint(bigint b, bigint a)
{
    if (bigint_is_equal_int(0,b))
    {
        bigint_set_zero(a);
        return;
    }

    bool _positive_a = bigint_is_positive(a);
    bool _positive_b = bigint_is_positive(b);
    bool opposite = _positive_a ^ _positive_b;
    bigint_absolute(b); // abs(b)
    bigint_absolute(a); // abs(a)

    // abs(a)<abs(b)
    if (bigint_is_less_bigint(a,b))
        return;
    // log2(abs(a)) == log2(abs(b))  <=>  b < a < 2*b
    if (bigint_log2(a) == bigint_log2(b))
        bigint_sub_bigint(b,a);
    // abs(a) >= 2*abs(b)
    else
    {
        bigint _mul_b; // _mul_b = 2^x * abs(b)
        i16 diff = bigint_log2(a) - bigint_log2(b);

        bigint_set_bigint(b,_mul_b);
        bigint_shift_bit_left(_mul_b, diff);

        if (bigint_is_less_bigint(a,_mul_b))
            bigint_shift_bit_right(_mul_b,1);

        while (!bigint_is_less_bigint(a,b)) // r > 2^x * abs(b)
        {
            bigint_sub_bigint(_mul_b, a); // r -= 2^_x *b

            //shift right _mul_b until binary length _mul_b = binary length r
            diff = bigint_log2(_mul_b) - bigint_log2(a);
            bigint_shift_bit_right(_mul_b,diff);
            if (bigint_is_less_bigint(a,_mul_b))
                bigint_shift_bit_right(_mul_b,1);
        }
    }

    //set sign
    if (!_positive_b)
        bigint_opposite(b);
    if (!_positive_a)
        bigint_opposite(a);
}
// res = a % b // &res != &a != &b
void bigint_mod_bigint_res(bigint b, bigint a, bigint res)
{
    if (bigint_is_equal_int(0,b))
    {
        bigint_set_zero(a);
        return;
    }

    bool _positive_a = bigint_is_positive(a);
    bool _positive_b = bigint_is_positive(b);
    bool opposite = _positive_a ^ _positive_b;
    bigint_absolute(b); // abs(b)
    bigint_absolute(a); // abs(a)

    // abs(a)<abs(b)
    if (bigint_is_less_bigint(a,b))
        return;
    // log2(abs(a)) == log2(abs(b))  <=>  b < a < 2*b
    if (bigint_log2(a) == bigint_log2(b))
        bigint_sub_bigint(b,a);
    // abs(a) >= 2*abs(b)
    else
    {
        bigint_set_bigint(a,res);

        bigint _mul_b; // _mul_b = 2^x * abs(b)
        i16 diff = bigint_log2(res) - bigint_log2(b);

        bigint_set_bigint(b,_mul_b);
        bigint_shift_bit_left(_mul_b, diff);

        if (bigint_is_less_bigint(res,_mul_b))
            bigint_shift_bit_right(_mul_b,1);

        while (!bigint_is_less_bigint(res,b)) // r > 2^x * abs(b)
        {
            bigint_sub_bigint(_mul_b, res); // r -= 2^_x *b

            //shift right _mul_b until binary length _mul_b = binary length r
            diff = bigint_log2(_mul_b) - bigint_log2(res);
            bigint_shift_bit_right(_mul_b,diff);
            if (bigint_is_less_bigint(res,_mul_b))
                bigint_shift_bit_right(_mul_b,1);
        }
    }

    //set sign
    if (!_positive_b)
        bigint_opposite(b);
    if (!_positive_a)
        bigint_opposite(a);
    if (!_positive_a)
        bigint_opposite(res);
}
// a %= b
void bigint_mod_int(i16 b, bigint a)
{
    i16 r = 0;
    if (b<0)
        b = -b;
    bool _positive_a = bigint_is_positive(a);
    bigint_absolute(a);

    for (ii i = BIGINT_LEN - 1; i>=0; i--)
        r = (r * BIGINT_BASE + a[i]) % b;

    if (!_positive_a)
        r = -r;
    bigint_set_int(r,a);
}
// r = a % b // &a != &b
void bigint_mod_int_res(i16 b, bigint a, i16* r)
{
    *r = 0;
    if (b<0)
        b = -b;
    bool _positive_a = bigint_is_positive(a);
    bigint_absolute(a);

    for (ii i = BIGINT_LEN - 1; i>=0; i--)
        *r = (*r * BIGINT_BASE + a[i]) % b;

    if (!_positive_a)
        *r = -*r;
}
#endif


