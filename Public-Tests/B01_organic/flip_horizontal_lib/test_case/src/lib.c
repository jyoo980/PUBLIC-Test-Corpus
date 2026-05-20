#include "lib.h"

void flip_horizontal(cp_image_t *img)
    __CPROVER_requires(__CPROVER_is_fresh(img, sizeof(*img)))
    __CPROVER_requires(img->w >= 2 && img->h >= 2)
    __CPROVER_requires(img->w <= 4 && img->h <= 4)
    __CPROVER_requires(__CPROVER_is_fresh(img->pix, img->w * img->h * sizeof(cp_pixel_t)))
    __CPROVER_assigns(__CPROVER_object_upto(img->pix, img->w * img->h * sizeof(cp_pixel_t)))
    __CPROVER_ensures(img->w == __CPROVER_old(img->w))
    __CPROVER_ensures(img->h == __CPROVER_old(img->h))
    __CPROVER_ensures(__CPROVER_pointer_equals(img->pix, __CPROVER_old(img->pix)))
{
    cp_pixel_t *pix = img->pix;
    int w = img->w;
    int h = img->h;
    int flips = h / 2;
    for (int i = 0; i < flips; ++i) {
        cp_pixel_t *a = pix + w * i;
        cp_pixel_t *b = pix + w * (h - i - 1);
        for (int j = 0; j < w; ++j) {
            cp_pixel_t t = *a;
            *a = *b;
            *b = t;
            ++a;
            ++b;
        }
    }
}
