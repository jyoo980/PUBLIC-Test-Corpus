#include <stddef.h>
#include <stdlib.h>

#include "lib.h"

char *bin2hex(char *hex, size_t hex_maxlen, const uint8_t *bin,
                    size_t bin_len)
    __CPROVER_requires(bin_len < (18446744073709551615UL) / 2)
    __CPROVER_requires(hex_maxlen > bin_len * 2U)
    __CPROVER_requires(__CPROVER_is_fresh(hex, hex_maxlen))
    __CPROVER_requires(__CPROVER_is_fresh(bin, bin_len))
    __CPROVER_assigns(__CPROVER_object_whole(hex))
    __CPROVER_ensures(__CPROVER_return_value == hex)
    __CPROVER_ensures(hex[bin_len * 2U] == 0)
    __CPROVER_ensures(__CPROVER_forall {
        size_t k1;
        (k1 < bin_len) ==> (
            (unsigned char)hex[k1 * 2U] ==
                (unsigned char)(87U + (bin[k1] & 0xf) +
                    ((((bin[k1] & 0xf) - 10U) >> 8) & ~38U))
        )
    })
    __CPROVER_ensures(__CPROVER_forall {
        size_t k2;
        (k2 < bin_len) ==> (
            (unsigned char)hex[k2 * 2U + 1U] ==
                (unsigned char)(87U + (bin[k2] >> 4) +
                    ((((bin[k2] >> 4) - 10U) >> 8) & ~38U))
        )
    })
{
    size_t i = (size_t)0U;
    unsigned int x;
    int b;
    int c;
    if (bin_len >= (18446744073709551615UL) / 2 || hex_maxlen <= bin_len * 2U) {
        abort();
    }
    while (i < bin_len) {
        c = bin[i] & 0xf;
        b = bin[i] >> 4;
        x = (unsigned char)(87U + c + (((c - 10U) >> 8) & ~38U)) << 8 |
            (unsigned char)(87U + b + (((b - 10U) >> 8) & ~38U));
        hex[i * 2U] = (char)x;
        x >>= 8;
        hex[i * 2U + 1U] = (char)x;
        i++;
    }
    hex[i * 2U] = 0U;
    return hex;
}
