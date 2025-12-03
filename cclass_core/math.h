#ifndef C_CLASS_CORE_MATH_HCLASS
#define C_CLASS_CORE_MATH_HCLASS

#include "cclass.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// NOTE(A-Boring-Square): This is completely freestanding except needing the FPU for floating point ops

/* ------------------ Basic constants ------------------ */
// Numeric zero
#define ZERO        0.0
// Numeric one
#define ONE         1.0
// Numeric two
#define TWO         2.0
// One-half
#define HALF        0.5
// Negative one
#define NEG_ONE    -1.0

/* ------------------ Circle constants ------------------ */
// Pi
#define PI          3.141592653589793238462643
// 2*Pi
#define TAU         6.283185307179586476925287

/* ------------------ Square roots ------------------ */
// sqrt(2)
#define SQRT2       1.4142135623730950488016887242097
// sqrt(3)
#define SQRT3       1.7320508075688772935274463415059
// sqrt(5)
#define SQRT5       2.2360679774997896964091736687313

/* ------------------ Cube roots ------------------ */
// cbrt(2)
#define CUBE_ROOT2  1.2599210498948731647672106072782
// cbrt(3)
#define CUBE_ROOT3  1.4422495703074083823216383107801

/* ------------------ Special ratios ------------------ */
// Golden ratio
#define PHI         1.6180339887498948482045868343656
// Silver ratio
#define SILVER      2.4142135623730950488016887242097

/* ------------------ Exponential/logarithmic constants ------------------ */
// Euler's number
#define E           2.7182818284590452353602874713527
// ln(2)
#define LN2         0.69314718055994530941723212145818

/* ------------------ Other mathematical constants ------------------ */
// Euler–Mascheroni constant
#define GAMMA      0.57721566490153286060651209008240
// Apery's constant ζ(3)
#define APERYS     1.2020569031595942853997381615110
// Omega constant W(1)
#define OMEGA      0.5671432904097838729999686622
// Catalan's constant
#define CATALAN    0.9159655941772190150546035149
// Soldner's constant
#define SOLDNER    1.4513692348833801508054024810
// Kepler–Bouwkamp constant
#define KEPLER     0.11494204485329620070
// Lemniscate constant
#define LEMNISCATE 2.622057554292119810463

/* ------------------ Utility macros ------------------ */
// Checks if X is a power of 2
#define IS_POWER_OF_2(X) ((X) != 0 && (((X) & ((X) - 1)) == 0))

/* ------------------ Type-generic math macros ------------------ */
// Trigonometry
// Sine
#define sin(x) _Generic((x), float: _sin_float, double: _sin_double)(x)
// Cosine
#define cos(x) _Generic((x), float: _cos_float, double: _cos_double)(x)
// Tangent
#define tan(x) _Generic((x), float: _tan_float, double: _tan_double)(x)
// Arcsine
#define asin(x) _Generic((x), float: _asin_float, double: _asin_double)(x)
// Arccosine
#define acos(x) _Generic((x), float: _acos_float, double: _acos_double)(x)
// Arctangent
#define atan(x) _Generic((x), float: _atan_float, double: _atan_double)(x)
// Two-argument arctangent
#define atan2(y,x) _Generic((y), float: _atan2_float, double: _atan2_double)(y,x)

// Hyperbolic
// Hyperbolic sine
#define sinh(x) _Generic((x), float: _sinh_float, double: _sinh_double)(x)
// Hyperbolic cosine
#define cosh(x) _Generic((x), float: _cosh_float, double: _cosh_double)(x)
// Hyperbolic tangent
#define tanh(x) _Generic((x), float: _tanh_float, double: _tanh_double)(x)
// Hyperbolic arcsine
#define asinh(x) _Generic((x), float: _asinh_float, double: _asinh_double)(x)
// Hyperbolic arccosine
#define acosh(x) _Generic((x), float: _acosh_float, double: _acosh_double)(x)
// Hyperbolic arctangent
#define atanh(x) _Generic((x), float: _atanh_float, double: _atanh_double)(x)

// Exponentials / logarithms
// Exponential e^x
#define exp(x) _Generic((x), float: _exp_float, double: _exp_double)(x)
// Natural logarithm
#define log(x) _Generic((x), float: _log_float, double: _log_double)(x)
// Base-10 logarithm
#define log10(x) _Generic((x), float: _log10_float, double: _log10_double)(x)
// Logarithm base y
#define logn(x,y) _Generic((x), float: _logn_float, double: _logn_double)(x,y)
// Power x^y
#define pow(x,y) _Generic((x), float: _pow_float, double: _pow_double)(x,y)
// Square root
#define sqrt(x) _Generic((x), float: _sqrt_float, double: _sqrt_double)(x)
// Cube root
#define cbrt(x) _Generic((x), float: _cbrt_float, double: _cbrt_double)(x)
// y-th root
#define root(x,y) _Generic((x), float: _root_float, double: _root_double)(x,y)

// Rounding and remainder
// Floor
#define floor(x) _Generic((x), float: _floor_float, double: _floor_double)(x)
// Ceiling
#define ceil(x)  _Generic((x), float: _ceil_float, double: _ceil_double)(x)
// Round to nearest
#define round(x) _Generic((x), float: _round_float, double: _round_double)(x)
// Truncate
#define trunc(x) _Generic((x), float: _trunc_float, double: _trunc_double)(x)
// Floating-point remainder
#define fmod(x,y) _Generic((x), float: _fmod_float, double: _fmod_double)(x,y)

// Absolute value only
#define abs(x) _Generic((x), \
    int: _abs_int, int8_t: _abs_int8, int16_t: _abs_int16, int32_t: _abs_int32, int64_t: _abs_int64, \
    float: _abs_float, double: _abs_double)(x)

/* ------------------ Common algorithms ------------------ */
// Clamp value to range [min,max]
#define clamp(x,min,max) _Generic((x), float: _clamp_float, double: _clamp_double, int: _clamp_int)(x,min,max)
// Linear interpolation
#define lerp(a,b,t) _Generic((a), float: _lerp_float, double: _lerp_double)(a,b,t)

/* ------------------ Linear algebra macros ------------------ */
// Vector addition: a[i] += b[i]
#define vec_add(a,b,n) \
    do { \
        SIMD_HINT \
        for(size_t i=0;i<(n);i++) \
            (a)[i] += (b)[i]; \
    } while(0)

// Vector subtraction: a[i] -= b[i]
#define vec_sub(a,b,n) \
    do { \
        SIMD_HINT \
        for(size_t i=0;i<(n);i++) \
            (a)[i] -= (b)[i]; \
    } while(0)

// Vector scaling: a[i] *= s
#define vec_scale(a,s,n) \
    do { \
        SIMD_HINT \
        for(size_t i=0;i<(n);i++) \
            (a)[i] *= (s); \
    } while(0)

/* ------------------ Floating-point calculus helpers ------------------ */
// Central difference numerical derivative: f'(x) ≈ (f(x+h) - f(x-h)) / 2h
#define derivative(f,x,h) _Generic((x), float: _derivative_float, double: _derivative_double)(f,x,h)
// Riemann sum numerical integral: ∫f(x) dx ≈ Σ f(x_i) * dx
#define integral(f,a,b,n) _Generic((a), float: _integral_float, double: _integral_double)(f,a,b,n)
// Summation of array elements
#define sum(arr,n) _Generic((arr[0]), float: _sum_float, double: _sum_double)(arr,n)
// Mean (average) of array elements
#define mean(arr,n) _Generic((arr[0]), float: _mean_float, double: _mean_double)(arr,n)
// Standard deviation of array elements
#define stddev(arr,n) _Generic((arr[0]), float: _stddev_float, double: _stddev_double)(arr,n)

#endif // C_CLASS_CORE_MATH_HCLASS
