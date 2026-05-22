// © 2026 Massachusetts Institute of Technology
// MIT License

#include "driver.h"

#include <stdbool.h>
#include <stdio.h>

typedef struct {
    unsigned int x : 2;
    unsigned int y : 3;
    bool b : 1;
    int z;
} foo_t;

void print_foo(const foo_t *foo)
__CPROVER_requires(__CPROVER_is_fresh(foo, sizeof(*foo)))
__CPROVER_assigns()
{
    printf("%u %u %d %d\n", foo->x, foo->y, foo->b, foo->z);
}

void driver(unsigned int x, unsigned int y, bool b, int z)
__CPROVER_assigns()
{
    foo_t foo = {.x = x, .y = y, .b = b, .z = z};
    print_foo(&foo);
}
