#ifndef __BIGINT_BITS__
#define __BIGINT_BITS__

#include "BigInt_Conf.h"
#include "bool.h"

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
#endif
