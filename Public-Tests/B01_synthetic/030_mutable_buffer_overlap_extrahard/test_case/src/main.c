// © 2026 Massachusetts Institute of Technology
// MIT License

#include <stdio.h>

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

void driver(int *out, int len)
__CPROVER_requires(len >= 0 && len <= 100 && __CPROVER_is_fresh(out, (size_t)len * sizeof(int)))
__CPROVER_assigns(__CPROVER_object_upto(out, (size_t)len * sizeof(int)))
{
    fma_array(out, out, out, out, len);
    for (int i = 0; i < len; i++) {
        printf("%d\n", out[i]);
    }
}

int main() {
    int data[100];
    int i;
    for (i = 0; i < 100; i++) {
        if (scanf("%d", &data[i]) != 1) {
            break;
        }
    }

    driver(data, i);
    return 0;
}