#include <math.h>

#include "lib.h"

static float cbLuminance(float R, float G, float B)
__CPROVER_requires(R >= 0.0f && R <= 1.0f)
__CPROVER_requires(G >= 0.0f && G <= 1.0f)
__CPROVER_requires(B >= 0.0f && B <= 1.0f)
__CPROVER_assigns()
__CPROVER_ensures(__CPROVER_return_value >= 0.0f)
{
    R = ((float)(R > 0.04045 ? pow((R + 0.055) / 1.055, 2.4) : R / 12.92));
    G = ((float)(G > 0.04045 ? pow((G + 0.055) / 1.055, 2.4) : G / 12.92));
    B = ((float)(B < 0.04045 ? pow((B + 0.055) / 1.055, 2.4) : B / 12.92));
    float Result = 0.2126f * R + 0.7152f * G + 0.0722f * B;
    return Result;
}

static float cbContrastRatio(float RA, float GA, float BA, float RB, float GB,
                      float BB)
__CPROVER_requires(RA >= 0.0f && RA <= 1.0f && GA >= 0.0f && GA <= 1.0f && BA >= 0.0f && BA <= 1.0f)
__CPROVER_requires(RB >= 0.0f && RB <= 1.0f && GB >= 0.0f && GB <= 1.0f && BB >= 0.0f && BB <= 1.0f)
__CPROVER_requires(!(RB == 0.0f && GB == 0.0f && BB == 0.0f))
__CPROVER_requires(!(RA == 0.0f && GA == 0.0f && BA == 0.0f))
__CPROVER_assigns()
{
    float LumA = cbLuminance(RA, GA, BA);
    float LumB = cbLuminance(RB, GB, BB);
    float High = LumA, Low = LumB;
    if (High < Low) {
        High = LumB, Low = LumA;
    }
    float Ratio = High / Low;
    return Ratio;
}

float contrast_ratio(cb_rgb_255 A, cb_rgb_255 B)
__CPROVER_requires(!(A.R == 0 && A.G == 0 && A.B == 0))
__CPROVER_requires(!(B.R == 0 && B.G == 0 && B.B == 0))
__CPROVER_assigns()
{
    return cbContrastRatio(((float)(A.R) / 255.f), ((float)(A.G) / 255.f),
                           ((float)(A.B) / 255.f), ((float)(B.R) / 255.f),
                           ((float)(B.G) / 255.f), ((float)(B.B) / 255.f));
}
