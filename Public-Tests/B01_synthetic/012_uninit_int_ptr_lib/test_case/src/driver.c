// © 2026 Massachusetts Institute of Technology
// MIT License

#include "driver.h"

#include <stdio.h>

void printIntPtrLine(const int *intNumber)
__CPROVER_requires(__CPROVER_is_fresh(intNumber, sizeof(*intNumber)))
__CPROVER_assigns()
{
    printf("%d\n", *intNumber);
}

void bad()
{
    int *data;
    printIntPtrLine(data);
}

void good()
{
    int data;
    data = 5;
    int *data_addr;
    data_addr = &data;
    printIntPtrLine(data_addr);
}

void driver(int useGood)
{
    if (useGood)
    {
        good();
    }
    else
    {
        bad();
    }
}
