#include "lib.h"

void rgb_to_hsv(float *dest, const float *src)
__CPROVER_requires(__CPROVER_is_fresh(dest, 3 * sizeof(float)))
__CPROVER_requires(__CPROVER_is_fresh(src, 3 * sizeof(float)))
__CPROVER_requires(src[0] >= 0.0f && src[0] <= 1.0f)
__CPROVER_requires(src[1] >= 0.0f && src[1] <= 1.0f)
__CPROVER_requires(src[2] >= 0.0f && src[2] <= 1.0f)
__CPROVER_assigns(dest[0], dest[1], dest[2])
__CPROVER_ensures(dest[1] >= 0.0f && dest[1] <= 1.0f)
__CPROVER_ensures(dest[2] >= 0.0f && dest[2] <= 1.0f)
__CPROVER_ensures(dest[0] >= 0.0f && dest[0] < 360.0f)
{
    float r = src[0];
    float g = src[1];
    float b = src[2];
    float h = 0;
    float s = 0;
    float v = 0;
    float min = r;
    float max = r;
    float delta;
    min = (((min) < (g)) ? (min) : (g));
    min = (((min) < (b)) ? (min) : (b));
    max = (((max) > (g)) ? (max) : (g));
    max = (((max) > (b)) ? (max) : (b));
    delta = max - min;
    v = max;
    if (delta == 0 || max == 0) {
        dest[0] = h;
        dest[1] = s;
        dest[2] = v;
        return;
    }
    s = delta / max;
    if (r == max)
        h = (g - b) / delta;
    else if (g == max)
        h = 2 + (b - r) / delta;
    else
        h = 4 + (r - g) / delta;
    h *= 60;
    if (h < 0)
        h += 360;
    dest[0] = h;
    dest[1] = s;
    dest[2] = v;
}
