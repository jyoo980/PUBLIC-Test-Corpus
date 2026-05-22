// © 2026 Massachusetts Institute of Technology
// MIT License

#include "driver.h"

#include <stdio.h>
#include <string.h>

void fma_array(int *out, const int *mul1, const int *mul2, const int *add, int len)
__CPROVER_requires(len >= 0 && len <= 100)
__CPROVER_requires(__CPROVER_is_fresh(out, (size_t)len * sizeof(int)))
__CPROVER_requires((const int *)out == mul1)
__CPROVER_requires((const int *)out == mul2)
__CPROVER_requires((const int *)out == add)
__CPROVER_assigns(__CPROVER_object_upto(out, (size_t)len * sizeof(int)))
{
    for (int i = 0; i < len; i++) {
        out[i] = mul1[i] * mul2[i] + add[i];
    }
}

static void inner(int *out, int len)
__CPROVER_requires(len >= 0 && len <= 100 && __CPROVER_is_fresh(out, (size_t)len * sizeof(int)))
__CPROVER_assigns(__CPROVER_object_upto(out, (size_t)len * sizeof(int)))
{
    fma_array(out, out, out, out, len);
    for (int i = 0; i < len; i++) {
        printf("%d\n", out[i]);
    }
}

void driver(const int *data, int len)
__CPROVER_requires(len >= 0 && len <= 100 && __CPROVER_is_fresh(data, (size_t)len * sizeof(int)))
__CPROVER_assigns()
{
    int out[len];
    memcpy(out, data, len * sizeof(int));
    inner(out, len);
}
