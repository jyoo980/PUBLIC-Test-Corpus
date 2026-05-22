// © 2026 Massachusetts Institute of Technology
// MIT License

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int floors;
    int bedrooms;
    double bathrooms;
} house_t;

static house_t the_house = {.floors = 2, .bedrooms = 5, .bathrooms = 2.5};

static void add_floor(house_t *house)
__CPROVER_requires(__CPROVER_is_fresh(house, sizeof(*house)))
__CPROVER_requires(house->floors < 2147483647)
__CPROVER_assigns(house->floors)
__CPROVER_ensures(house->floors == __CPROVER_old(*house).floors + 1)
{
    house->floors++;
}

static void add_bedrooms(house_t *house, int extra_bedrooms)
__CPROVER_requires(__CPROVER_is_fresh(house, sizeof(*house)))
__CPROVER_requires(extra_bedrooms >= 0 && house->bedrooms <= 2147483647 - extra_bedrooms)
__CPROVER_requires(extra_bedrooms < 0 ? house->bedrooms >= -2147483647 - extra_bedrooms : 1)
__CPROVER_assigns(house->bedrooms)
__CPROVER_ensures(house->bedrooms == __CPROVER_old(*house).bedrooms + extra_bedrooms)
{
    house->bedrooms += extra_bedrooms;
}

static void add_floor_to_the_house()
__CPROVER_requires(the_house.floors < 2147483647)
__CPROVER_assigns(the_house.floors)
{
    add_floor(&the_house);
}

static void print_the_house()
__CPROVER_assigns()
{
    printf("The house has %d floors, %d bedrooms, and %.1f bathrooms\n", the_house.floors, the_house.bedrooms, the_house.bathrooms);
}

void run(int extra_bedrooms) {
    print_the_house();
    add_floor_to_the_house();
    print_the_house();
    the_house.bathrooms += 1.0;
    print_the_house();
    add_bedrooms(&the_house, extra_bedrooms);
    print_the_house();
}

int main() {
    int x = 0;
    scanf("%d", &x);
    run(x);
    run(x);
    return 0;
}