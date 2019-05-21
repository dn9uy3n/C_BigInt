#ifndef __BIGINT_PRINT__
#define __BIGINT_PRINT__

#include <stdio.h>
#include "BigInt_Conf.h"
#include "BigInt_Set.h"
#include "BigInt_Comp.h"
#include "BigInt_Math_Mul.h"

void bigint_print_arr(bigint a)
{
    for (ii i = BIGINT_LEN - 1; i >= 0; i--)
        printf("%3d", a[i]);
    printf("\n");
}

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
