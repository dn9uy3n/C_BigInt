# C_BigInt
Big Integer for C99.

Numbers are represented in array of byte:
N = a[0] + a[1] + ... + a[BIGINT_LEN-1]

BIGINT_LEN can be changed.


. Header-Only

. Optimized



Sample:

```c
#include <stdio.h>
#include "BigInt.h"

int main()
{
    bigint a;
    bigint_set_int(50,a);

    bigint b;
    bigint_set_bigint(a,b);
    bigint_sub_int(20,b);

    bigint_print_dec(a);
    printf("*");
    bigint_print_dec(b);
    printf(" = ");
    bigint_mul_bigint(b,a);
    bigint_print_dec(a);
    printf("\n");

    bigint c;
    bigint_set_int(22,c);

    bigint d,e;

    bigint_divide_bigint(c,a,d,e);

    bigint_print_dec(c);
    printf("*");
    bigint_print_dec(d);
    printf(" + ");
    bigint_print_dec(e);
    printf(" = ");
    bigint_print_dec(a);

    return 0;
}

```

