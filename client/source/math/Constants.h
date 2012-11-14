#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "Types.h"

namespace revel 
{ 
namespace math
{

/// Approximation of pi
static const f32 PI = 3.14159265358979323846f;
/// Approximation of 2*pi
static const f32 TWO_PI = 6.28318530717958623200f;
/// Approximation of pi/2
static const f32 PI_OVER_TWO = 1.57079632679489661923f;

/// Approximation of the inverse of pi
static const f32 PI_INVERSE = 0.31830988618379069122f;
/// Epsilon defined as the small number 10^(-5)
static const f32 EPSILON = 1.0e-5f;
/// Approximation of pi/180
static const f32 PI_OVER_180 = 0.0174532925f;
/// Approximation of pi/360
static const f32 PI_OVER_360 = 0.008726646f;
/// Approximation of the inverse of pi/180
static const f32 PI_OVER_180_INVERSE = 57.2957795f;

} // ::revel::math
} // ::revel

#endif // CONSTANTS_H_
