#ifndef C_CLASS_CORE_MATH_HCLASS
#define C_CLASS_CORE_MATH_HCLASS
#include "cclass.h"
#include "types.h"
#include <stdint.h>
#include <stdbool.h>


/* Basic constants */
#define ZERO       0.0                  // Zero
#define ONE        1.0                  // One
#define TWO        2.0                  // Two
#define HALF       0.5                  // One-half
#define NEG_ONE   -1.0                  // Negative one

/* Circle constants */
#define PI        3.141592653589793238462643      // Pi, ratio of circumference to diameter
#define TAU       6.283185307179586476925287      // Tau, 2*Pi

/* Square roots */
#define SQRT2     1.4142135623730950488016887242097  // Square root of 2
#define SQRT3     1.7320508075688772935274463415059  // Square root of 3
#define SQRT5     2.2360679774997896964091736687313  // Square root of 5

/* Cube roots */
#define CUBE_ROOT2 1.2599210498948731647672106072782 // Cube root of 2
#define CUBE_ROOT3 1.4422495703074083823216383107801 // Cube root of 3

/* Special ratios */
#define PHI       1.6180339887498948482045868343656  // Golden ratio
#define SILVER    2.4142135623730950488016887242097  // Silver ratio

/* Exponential/logarithmic constants */
#define E         2.7182818284590452353602874713527  // Euler's number
#define LN2       0.69314718055994530941723212145818 // Natural log of 2

/* Other mathematical constants */
#define GAMMA      0.57721566490153286060651209008240 // Euler–Mascheroni constant
#define APERYS     1.2020569031595942853997381615110  // Apery's constant ζ(3)
#define OMEGA      0.5671432904097838729999686622     // Omega constant W(1)
#define CATALAN    0.9159655941772190150546035149     // Catalan's constant
#define SOLDNER    1.4513692348833801508054024810     // Soldner's constant
#define KEPLER     0.11494204485329620070             // Kepler–Bouwkamp constant
#define LEMNISCATE 2.622057554292119810463            // Lemniscate constant

#define IsPowerOf2(X) ((X) != 0 && (((X) & ((X) - 1)) == 0))


#define sin(x) _Generic( \
    float: _sin_float, \
    double: _sin_double, \
)

#endif // C_CLASS_CORE_MATH_HCLASS