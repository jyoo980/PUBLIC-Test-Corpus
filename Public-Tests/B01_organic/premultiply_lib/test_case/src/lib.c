#include "lib.h"

void premultiply(cp_image_t *img)
__CPROVER_requires(__CPROVER_is_fresh(img, sizeof(cp_image_t)))
__CPROVER_requires(img->w >= 1 && img->w <= 2)
__CPROVER_requires(img->h >= 1 && img->h <= 2)
__CPROVER_requires(__CPROVER_is_fresh(img->pix, img->w * img->h * sizeof(cp_pixel_t)))
__CPROVER_assigns(__CPROVER_object_whole(img->pix))
__CPROVER_ensures(__CPROVER_forall {
    int k; (k >= 0 && k < __CPROVER_old(img->w) * __CPROVER_old(img->h)) ==>
        img->pix[k].a == __CPROVER_old(img->pix[k].a)
})
{
    int w = img->w;
    int h = img->h;
    int stride = w * sizeof(cp_pixel_t);
    uint8_t *data = (uint8_t *)img->pix;
    for (int i = 0; i < (int)stride * h; i += sizeof(cp_pixel_t)) {
        float a = (float)data[i + 3] / 255.0f;
        float r = (float)data[i + 0] / 255.0f;
        float g = (float)data[i + 1] / 255.0f;
        float b = (float)data[i + 2] / 255.0f;
        r *= a;
        g *= a;
        b *= a;
        data[i + 0] = (uint8_t)(r * 255.0f);
        data[i + 1] = (uint8_t)(g * 255.0f);
        data[i + 2] = (uint8_t)(b * 255.0f);
    }
}
