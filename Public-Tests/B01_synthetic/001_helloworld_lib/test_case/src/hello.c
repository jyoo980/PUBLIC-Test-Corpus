// © 2026 Massachusetts Institute of Technology
// MIT License

#include <stdio.h>

#include "hello.h"

int helloworld()
__CPROVER_assigns()
__CPROVER_ensures(__CPROVER_return_value == 0)
{
    printf("Hello World!\n");
    return 0;
}
