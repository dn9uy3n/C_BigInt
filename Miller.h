#ifndef __Miller__

#include "BigInt.h"
// Miller-Robin primality test
// return false: number n is composite
// return true:  number n is very likely to be a prime
//
bool miller_test_prime(bigint n, uin trials)
{
    if (bigint_is_even(n))
        return false;

    bigint n_1; bigint_set_bigint(n, n_1); bigint_sub_int(1, n_1);

    uin s = 0;
    bigint m;
    bigint_set_bigint(n_1, m);
    while (bigint_is_even(m))
    {
        s++;
        bigint_shift_bit_right(m, 1);
    }

    bigint d;
    {
        bigint_set_bigint(n_1,m);
        bigint t;
        bigint_set_int(1, t);
        bigint r;
        bigint_shift_bit_left(t, s);
        bigint_divide_bigint(t, m, d, r);
    }

    if (trials == 0)
        trials = 3;

    for (ii i=0; i < trials; i++)
    {
        bigint a;
        {
            bigint _max; bigint_set_bigint(n, _max); bigint_sub_int(4,_max);
            bigint_rand_range(a, _max);
            bigint_add_int(2, a);
        }

        bigint x;
        bigint_pow_mod_bigint(a, d, n, x);

        if (bigint_is_equal_int(1, x) || bigint_is_equal_bigint(x, n_1))
            continue;
        for (ii r = 0; r < s - 1; r++)
        {
            bigint x2, g;
            bigint_set_bigint(x,x2);
            bigint_mul_bigint(x, x2);
            bigint_mod_bigint_res(n, x2, g);
            bigint_set_bigint(g,x);

            if (bigint_is_equal_int(1,x))
                return false;

            if (bigint_is_equal_bigint(x, n_1))
                break;
        }

        if (!bigint_is_equal_bigint(x, n_1))
            return false;
    }
    return true;
}
#endif
