#ifndef COMMONMATH_H_
#define COMMONMATH_H_

#include "Constants.h"

namespace revel
{
namespace math
{

template <class T>
T deg_to_rad(T degrees)
{
    return degrees * math::PI_OVER_180;
}

template <class T>
T rad_to_deg(T radians)
{
    return radians * math::PI_OVER_180_INVERSE;
}

template <typename T>
inline T clamp(T value, T low, T high)
{
    if (value < low)
        return low;
    else if (value > high)
        return high;
    else
        return value;
}

inline bool is_power_of_2(i32 value)
{
    return (value & (value - 1)) == 0;
}

template <typename T>
inline T lerp(T t, T v1, T v2)
{
    return (1.0f - t) * v1 + t * v2;
}

template <typename T> inline
i32 ffloor(T x)
{
    if (x >= 0) 
        return static_cast<i32>(x);
    else
        return static_cast<i32>(x - 1);
}

inline
i32 floor_to_i32(f32 x)
{
    return ffloor(x);
}

/**
 * Returns remainder of a/b. Works with negative numbers unlike %.
 */
inline
i32 mod(i32 a, i32 b)
{
    i32 n = static_cast<i32>(a/b);
    a -= n*b;
    if (a < 0)
        a+=b;
    return a;
}

}} // ::revel::math

#endif // COMMONMATH_H_
