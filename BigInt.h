#ifndef __BIGINT__
#define __BIGINT__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BIGINT_LEN 129
#define BIGINT_SIZE BIGINT_LEN*8
#define BIGINT_DBITS 8
#define BIGINT_BASE 256

typedef uint8_t bigint[BIGINT_LEN];
typedef int16_t ii;
typedef int16_t i16;
typedef int32_t i32;

typedef uint8_t bool;
#define true 1
#define false 0

//-------------------------------------------------------------------//

//a = a << 8*sh (base 256)
void bigint_shift_digit_left(bigint a, i16 shift);
//a = a >> 8*shift (base 256)
void bigint_shift_digit_right(bigint a, i16 shift);
//a = a >> sh
void bigint_shift_bit_right(bigint a, i16 shift);
// a = a << sh
void bigint_shift_bit_left(bigint a, i16 shift);
// check if bit at pos is on
bool bigint_is_on_bit(bigint a, i16 pos);
// turn on bit at pos
void bigint_on_bit(bigint a, i16 pos);
// turn off bit at pos
void bigint_off_bit(bigint a, i16 pos);

// a = ~a
void bigint_reverse_bit(bigint a);
// a = 0
void bigint_set_zero(bigint a);
// a = b
void bigint_set_int(i16 b, bigint a);
// a = b
void bigint_set_bigint(bigint b, bigint a);

// a == b
bool bigint_is_equal_bigint(bigint b, bigint a);
// a == b
bool bigint_is_equal_int(i16 b, bigint a);
// a <= b
bool bigint_is_less_bigint(bigint a, bigint b);
// a <= b
bool bigint_is_less_equal_bigint(bigint a, bigint b);
// a <= b
bool bigint_is_less_equal_int(i16 a, bigint b);
// a % 2 == 0
bool bigint_is_even(bigint a);
// a % 2 == 1
bool bigint_is_odd(bigint a);
// return (a<0)
bool bigint_is_negative(bigint a);
// a>=0
bool bigint_is_positive(bigint a);

// return log2(a)
i16 bigint_log2(bigint a);

// a += b
void bigint_add_bigint(bigint b, bigint a);
// res = a + b // &res != {a,b}
void bigint_add_bigint_res(bigint b, bigint a, bigint res);
// a += b
void bigint_add_int(i16 b, bigint a);
// res = a + b // &res != {a}
void bigint_add_int_res(i16 b, bigint a, bigint res);
// a -= b
void bigint_sub_bigint(bigint b, bigint a);
// res = a - b // &res != {a,b}
void bigint_sub_bigint_res(bigint b, bigint a, bigint res);
// a -= b
void bigint_sub_int(i16 b, bigint a);
// res = a - b // &res != {a}
void bigint_sub_int_res(i16 b, bigint a, bigint res);
// a = -a
void bigint_opposite(bigint a);
// a = abs(a)
void bigint_absolute(bigint a);
// a *= b
void bigint_mul_int(i16 b, bigint a);
// res = a * b // &res != &a != &b
void bigint_mul_int_res(i16 b, bigint a, bigint res);
// a *= b // &a != &b
void bigint_mul_bigint(bigint b, bigint a);
// res = a * b // &res != &a != &b
void bigint_mul_bigint_res(bigint b, bigint a, bigint res);
// q = a / b; r = a % b // &a != &b != &q != &r // -abs(b) < r < abs(b)
void bigint_divide_bigint(bigint b, bigint a, bigint q, bigint r);
// a /= b // &a != &b
void bigint_div_bigint(bigint b, bigint a);
// res = a / b // &res != &a != &b
void bigint_div_bigint_res(bigint b, bigint a, bigint res);
// a /= b // &a != &b
void bigint_div_int(i16 b, bigint a);
// res = a / b // &res != &a != &b
void bigint_div_int_res(i16 b, bigint a, bigint res);
// a %= b // &a != &b
void bigint_mod_bigint(bigint b, bigint a);
// res = a % b // &res != &a != &b
void bigint_mod_bigint_res(bigint b, bigint a, bigint res);
// a %= b
void bigint_mod_int(i16 b, bigint a);
// r = a % b // &a != &b
void bigint_mod_int_res(i16 b, bigint a, i16* r);
// d = a^b mod c
void bigint_pow_mod_bigint(bigint a, bigint b, bigint c, bigint d);
// res = gcd(a,b) // &res != &a != &b
void bigint_gcd(bigint a, bigint b, bigint res);
// res = gcd(a,b), a*x + b*y = res // &res != &a != &b != &x != &y
void bigint_gcd_extend(bigint a, bigint b, bigint res, bigint x, bigint y);

// a = rand()
void bigint_rand(bigint a);
// a = rand() % lim
void bigint_rand_range(bigint a, bigint lim);

//print in base 256
void bigint_print_arr(bigint a);
//print in base 10
void bigint_print_dec(bigint a);

//-------------------------------------------------------------------//

//a = a << 8*sh (base 256)
void bigint_shift_digit_left(bigint a, i16 shift)
{
    if (shift <= 0)
        return;

    // shift = min(shift, BIGINT_LEN)
    if (shift > BIGINT_LEN)
        shift = BIGINT_LEN;

    for (ii i = BIGINT_LEN - 1; i >= shift; i--)
        a[i] = a[i - shift];

    for (ii i = 0; i < shift; i++)
        a[i] = 0;
}
//a = a >> 8*shift (base 256)
void bigint_shift_digit_right(bigint a, i16 shift)
{
    if (shift <= 0)
        return;

    // shift = min(shift, BIGINT_LEN)
    if (shift > BIGINT_LEN)
        shift = BIGINT_LEN;

    for (ii i = 0; i < BIGINT_LEN - shift; i++)
        a[i] = a[i + shift];

    for (ii i = 0; i < shift; i++)
        a[BIGINT_LEN - 1 - i] = 0;
}
//a = a >> sh
void bigint_shift_bit_right(bigint a, i16 shift)
{
    if (shift <= 0)
        return;

    bigint_shift_digit_right(a, shift / BIGINT_DBITS);
    shift %= BIGINT_DBITS;

    for (ii i=0; i<BIGINT_LEN-1; i++)
    {
        a[i] >>= shift;
        a[i] |= a[i+1]<<(BIGINT_DBITS - shift);
    }
    a[BIGINT_LEN-1] >>= shift;
}
// a = a << sh
void bigint_shift_bit_left(bigint a, i16 shift)
{
    if (shift <= 0)
        return;

    bigint_shift_digit_left(a, shift / BIGINT_DBITS);
    shift %= BIGINT_DBITS;

    for (ii i=BIGINT_LEN-1; i>0; i--)
    {
        a[i] <<= shift;
        a[i] |= a[i-1]>>(BIGINT_DBITS - shift);
    }
    a[0] <<= shift;
}
// check if bit at pos is on
bool bigint_is_on_bit(bigint a, i16 pos)
{
    if (pos>=BIGINT_SIZE || pos<0)
        return false;
    return a[pos/BIGINT_DBITS] & (1<<(pos%BIGINT_DBITS));
}
// turn on bit at pos
void bigint_on_bit(bigint a, i16 pos)
{
    if (pos>=BIGINT_SIZE || pos<0)
        return;
    a[pos/BIGINT_DBITS] |= (1<<(pos%BIGINT_DBITS));
}
// turn off bit at pos
void bigint_off_bit(bigint a, i16 pos)
{
    if (pos>=BIGINT_SIZE || pos<0)
        return;
    a[pos/BIGINT_DBITS] &= ~(1<<(pos%BIGINT_DBITS));
}
// a = ~a
void bigint_reverse_bit(bigint a)
{
    for (ii i=0; i<BIGINT_LEN; i++)
        a[i] = ~a[i];
}

// a = 0
void bigint_set_zero(bigint a)
{
    memset(a, 0, BIGINT_LEN);
}
// a = b
void bigint_set_int(i16 b, bigint a)
{
    bool negative = (b<0);
    if (negative)
        b = -b;
    for (ii i=0; i<BIGINT_LEN; i++)
    {
        a[i] = b % BIGINT_BASE;
        b /= BIGINT_BASE;
    }
    if (negative)
    {
        bigint_opposite(a);
    }
}
// a = b
void bigint_set_bigint(bigint b, bigint a)
{
    memcpy(a, b, BIGINT_LEN);
}

// a == b
bool bigint_is_equal_bigint(bigint b, bigint a)
{
    for (ii i=0; i<BIGINT_LEN; i++)
        if (a[i] != b[i])
            return false;
    return true;
}
// a == b
bool bigint_is_equal_int(i16 b, bigint a)
{
    bigint _b; bigint_set_int(b, _b);
    return bigint_is_equal_bigint(_b,a);
}
// a <= b
bool bigint_is_less_bigint(bigint a, bigint b)
{
    for (ii i = BIGINT_LEN - 1; i>=0; i--)
    {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return false;
}
// a <= b
bool bigint_is_less_equal_bigint(bigint a, bigint b)
{
    for (ii i = BIGINT_LEN - 1; i>=0; i--)
    {
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    return true;
}
// a <= b
bool bigint_is_less_equal_int(i16 a, bigint b)
{
    bigint _a; bigint_set_int(a,_a);
    return bigint_is_less_equal_bigint(_a,b);
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
// a>=0
bool bigint_is_positive(bigint a)
{
    return !(bigint_is_on_bit(a, BIGINT_SIZE-1));
}

// return log2(a)
i16 bigint_log2(bigint a)
{
    if (bigint_is_negative(a))
        return 0;
    for (ii i=BIGINT_LEN-1; i>=0; i--)
        if (a[i]!=0)
            for (ii j=7; j>=0; j--)
                if (a[i]&(1<<j))
                    return j+i*8;
    return 0;
}
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
        bigint_set_zero(a);
    else
    {
        // log2(abs(a)) == log2(abs(b))  <=>  b < a < 2*b
        if (bigint_log2(a) == bigint_log2(b))
            bigint_set_int(1,a);
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
        bigint_set_zero(res);
    else
    {
        // log2(abs(a)) == log2(abs(b))  <=>  b < a < 2*b
        if (bigint_log2(a) == bigint_log2(b))
            bigint_set_int(1,res);
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
    bigint _b;
    bigint_set_int(b,_b);
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
    bigint_absolute(b); // abs(b)
    bigint_absolute(a); // abs(a)

    // abs(a)<abs(b)
    if (bigint_is_less_bigint(a,b))
    {
    }
    else
    {
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
    bigint_absolute(b); // abs(b)
    bigint_absolute(a); // abs(a)

    // abs(a)<abs(b)
    if (bigint_is_less_bigint(a,b))
    {
        bigint_set_bigint(a,res);
    }
    else
    {

        // log2(abs(a)) == log2(abs(b))  <=>  b < a < 2*b
        if (bigint_log2(a) == bigint_log2(b))
        {
            bigint_set_bigint(a,res);
            bigint_sub_bigint(b,res);
        }
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
// d = a^b mod c
void bigint_pow_mod_bigint(bigint a, bigint b, bigint c, bigint d)
{
    bigint t, _a, _b;

    bigint_set_bigint(a,_a);
    bigint_set_bigint(b,_b);
    bigint_set_zero(t);
    bigint_set_int(1,d);

    while (!bigint_is_equal_int(0,_b))
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

//print in base 256
void bigint_print_arr(bigint a)
{
    for (ii i = BIGINT_LEN - 1; i >= 0; i--)
        printf("%3d", a[i]);
    printf("\n");
}
//print in base 10
void bigint_print_dec(bigint a)
{
    ii n = 0;
    char str[BIGINT_SIZE*4];
    memset(str, 0, 4096);

    bigint _a;
    bigint_set_bigint(a,_a);
    if (bigint_is_negative(_a))
        bigint_opposite(_a);


    i16 r;
    while (!bigint_is_equal_int(0, _a))
    {
        bigint_mod_int_res(10,_a,&r);
        str[n++] = '0' + r;
        bigint_div_int(10, _a);
    }
    if (n == 0)
        str[n++] = '0';
    if (bigint_is_negative(a))
        str[n++] = '-';
    for (ii i = n - 1; i >= 0; i--)
        printf("%c", str[i]);
    printf("\n");
}

#endif
