// © 2026 Massachusetts Institute of Technology
// MIT License

#include <stdio.h>

static void print_hex(unsigned char *p, int len)
__CPROVER_requires(len >= 0 && __CPROVER_is_fresh(p, (size_t)len))
__CPROVER_assigns()
{
    for (int i = 0; i < len; i++) {
        printf("%02x", p[i]);
    }
    printf("\n");
}

void driver(int x)
__CPROVER_assigns()
{
    print_hex((unsigned char *)&x, sizeof(x));
}

int main() {
    int x = 0;
    scanf("%d", &x);
    driver(x);
    return 0;
}