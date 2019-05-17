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
    char str[4096];
    memset(str, 0, 4096);

    ii n = 0;
    bigint _a;
    bigint_set_bigint(a, _a);

    while (!bigint_equal_int(0, _a))
    {
        str[n++] = '0' + bigint_mod_int_res(10,_a);
        bigint_div_int(10, _a);
    }
    if (n == 0)
        str[n++] = '0';
    for (ii i = n - 1; i >= 0; i--)
        printf("%c", str[i]);
    printf("\n");
}
#endif
