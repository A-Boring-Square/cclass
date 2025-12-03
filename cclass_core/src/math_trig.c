#include "cclass.h"
#include "math.h"
#include "types.h"

float _sin_float(float x) {
    SIMD_HINT
    for (; x > PI || x < -PI; ) {
        if (x > PI)  x -= TAU;
        if (x < -PI) x += TAU;
    }
    float x2 = x * x;
    return x * (1.0f - x2 * (1.0f/6.0f - x2*(1.0f/120.0f)));
}
double _sin_double(double x) {
    SIMD_HINT
    for (; x > PI || x < -PI; ) {
        if (x > PI)  x -= TAU;
        if (x < -PI) x += TAU;
    }
    double x2 = x * x;
    return x * (1.0 - x2 * (1.0/6.0 - x2 * (1.0/120.0 - x2*(1.0/5040.0))));
}
