// © 2026 Massachusetts Institute of Technology
// MIT License

#include "driver.h"

#include <stdio.h>

void driver(int x)
__CPROVER_requires(x >= -1073741673 && x <= 1073741673)
__CPROVER_assigns()
{
    auto int y = 2*x;
    y += 300;
    printf("%d\n", y);
}