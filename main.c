#include "BigInt_Math_Mul.h"
#include "BigInt_Print.h"

int main()
{
    bigint a;
    bigint_set_int(50,a);

    bigint b;
    bigint_set_int(121,b);

    bigint c,d;
    bigint_mod_int(43,a);

    bigint_print_arr(a);
}
int main2()
{
    int a = -5;
    int b = 2;
    int c = a%b;
    printf("%d",c);
}
