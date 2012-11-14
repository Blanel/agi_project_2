#ifndef _RVL_VECTOR3_H_
#define _RVL_VECTOR3_H_

#include "Types.h"
#include "math/Constants.h"
#include "math/Point3.h"
#include <cmath>

#include <memory>
#include <ostream>

namespace revel { namespace math
{

//forward declarations
template <typename T> class Vector2;

/**
 * Templated vector with 3 dimensions.
 *
 * Typical tests:
 * Colinear - check if (a dot b) = a * b
 * Colinear but opposite - check if (a dot b) = -(a * b)
 * Perpendicular - check if (a dot b) = 0
 * Same direction - check if (a dot b) > 0
 * Opposite direction - check if (a dot b) < 0
 */
template <typename T>
class Vector3
{
public:
    Vector3() {}
    Vector3(T a)
        : x(a)
        , y(a)
        , z(a)
    {}
    Vector3(T ix, T iy, T iz)
        : x(ix)
        , y(iy)
        , z(iz)
    {}
    Vector3(const Vector3& v)
        : x(v.x)
        , y(v.y)
        , z(v.z)
    {}
    Vector3(const Vector2<T>& v, T a)
        : x(v.x)
        , y(v.y)
        , z(a)
    {}
    Vector3(const T* p)
        : x(p[0])
        , y(p[1])
        , z(p[2])
    {}
    Vector3(const Point3<T>& p)
        : x(p.x)
        , y(p.y)
        , z(p.z)
    {}

    ~Vector3()
    {}

    /**
     * Assignement of all variables in the vector.
     *
     * @param[in] ix X value.
     * @param[in] iy Y value.
     * @param[in] iz Z value.
     *
     * @return Reference to itself.
     */
	Vector3&
	xyz(T ix, T iy, T iz)
	{
		x = ix;
		y = iy;
		z = iz;

        return *this;
	}

    /**
     * Get a pointer to the first element.
     *
     * @return The pointer.
     */
    const T* get_ptr() const
	{
		return &x;
	}

    /**
     * Assignment of a vector 
     *
     * @param v Input vector
     * @return Reference to itself
     */
    Vector3&
    operator=(const Vector3& v)
    {
        if (this != &v)
        {
            x = v.x; y = v.y; z = v.z;
        }
        return *this;
    }

    /**
     * Equality comparison of two vectors.
     *
     * @param v Vector
     * @param epsilon Small number which is an acceptable bound. Predefined as 10^(-5).
     * @return True if vectors are equal.
     */
    bool
    equal(const Vector3& v, T epsilon = math::EPSILON) const
    {
            return ((abs(x-v.x) > epsilon ||
             abs(y-v.y) > epsilon ||
             abs(z-v.z) > epsilon) ? 0 : 1);
    }

    /**
     * Equality comparison of two vectors.
     *
     * @param v Vector
     * @return True if vectors are equal.
     */
    bool
    operator==(const Vector3& v) const
    {
        return (x == v.x && y == v.y && z == v.z);
    }

    /**
     * Inequality comparison of two vectors.
     *
     * @param v Vector
     * @return True if vectors are NOT equal.
     */
    bool
    operator!=(const Vector3& v) const
    {
        return (!(*this == v));
    }

    /**
     * Negate a vector.
     * 
     * @return A negated vector
     */
    Vector3
    operator-() const
    {
        return Vector3(-x, -y, -z);
    }

    /**
     * Vector addition.
     *
     * @param v Vector to add with.
     * @return Vector result.
     */
    Vector3
    operator+(const Vector3& v) const
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    /**
     * Vector subtraction.
     *
     * @param v Vector to subtract with.
     * @return Vector result.
     */
    Vector3
    operator-(const Vector3& v) const
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    /**
     * Vector multiplication.
     *
     * @param v Vector to multiply with.
     * @return Vector result.
     */
    Vector3
    operator*(const Vector3& v) const
    {
        return Vector3(x * v.x, y * v.y, z * v.z);
    }

    /**
     * Vector addition.
     *
     * @param v Vector to add with.
     * @return Reference to itself
     */
    Vector3&
    operator+=(const Vector3& v)
    {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }

    /**
     * Vector subtraction.
     *
     * @param v Vector to subtract with.
     * @return Reference to itself
     */
    Vector3&
    operator-=(const Vector3& v)
    {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }

    /**
     * Vector multiplication.
     *
     * @param v Vector to multiply with.
     * @return Reference to itself
     */
    Vector3&
    operator*=(const Vector3& v)
    {
        x*=v.x; y*=v.y; z*=v.z;
        return *this;
    }

    /**
     * Multiply vector elements with a scalar.
     *
     * @param a Scalar to multiply with.
     * @return Vector result.
     */
    Vector3
    operator*(T a) const
    {
        return Vector3(x*a, y*a, z*a);
    }

    /**
     * Divide vector elements with a scalar.
     *
     * @param a Scalar to multiply with.
     * @return Vector result.
     */
    Vector3
    operator/(T a) const
    {
        return Vector3(x/a, y/a, z/a);
    }

    /**
     * Multiply vector elements with a scalar.
     *
     * @param a Scalar to multiply with.
     * @return Reference to itself.
     */
    Vector3&
    operator*=(T a)
    {
        x*=a; y*= a; z*= a;
        return *this;
    }

    /**
     * Divide vector elements with a scalar.
     *
     * @param a Scalar to divide with.
     * @return Reference to itself.
     */	
    Vector3&
    operator/=(T a)
    {
        x/=a; y*=a; z*=a;
        return *this;
    }

    /**
     * Array operator 
     *
     * @param x Index.
     * @return Reference to the element.
     */	
    T&
    operator[](i32 x)
    {
        return e[x];
    }

    /**
     * Array operator 
     *
     * @param x Index.
     * @return Copy of the element.
     */	
    T
    operator[](i32 x) const
    {
        return e[x];
    }

    /**
     * Calculate the euclidean distance
     *
     * @return Euclidean distance.
     */
    f32
    length() const
    {
        return sqrt(x*x + y*y + z*z);
    }

    /**
     * Calculate the euclidean distance squared.
     *
     * @return Euclidean distance squared.
     */
    f32
    length_squared() const
    {
        return (x*x + y*y + z*z);
    }

    /**
     * Calculate a normalized vector
     */
    Vector3
    normalized() const
    {
        f32 n = 1/length();
        if (n <= 0) 
            n = 1;

        return Vector3(x * n, y * n, z* n);
    }

    /**
     * Calculate the dot product between two vectors
     *
     * @param v Input vector
     * @return Vector with the cross product
     */
    Vector3
    cross(const Vector3& v) const
    {
        return Vector3<T>(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
    }

    friend std::ostream& operator<<(std::ostream &os, const Vector3& v)
    {
        os << v.x << " \t" << v.y << " \t" << v.z;

        return os;
    }

    union
    {
        struct { T x, y, z; };
        T e[3];
    };

    static const Vector3 Zero;
    static const Vector3 UnitX;
    static const Vector3 UnitY;
    static const Vector3 UnitZ;
};

template <typename T>
Vector3<T>& normalize(Vector3<T>& v)
{
    f32 n = 1/v.length();

    if (n <= 0)
        n = 1;

    v *= n;

    return v;
}

/*
template <typename T>
Vector3<T>& normalize(Vector3<T>&& v)
{
    return normalize<T>(std::ref(v));
}
*/

/**
 * Calculate the dot product between two vectors
 *
 * @param l Input vector (lhs)
 * @param r Input vector (rhs)
 * @return Scalar with the dot product
 */
template <typename T>
T
dot(const Vector3<T>& l, const Vector3<T>& r)
{
    return (l.x*r.x + l.y*r.y + l.z*r.z);
}

template <typename T>
Vector3<T>
cross(const Vector3<T>& l, const Vector3<T>& r)
{
    return Vector3<T>(l.y*r.z - l.z*r.y, l.z*r.x - l.x*r.z, l.x*r.y - l.y*r.x);
}

template <typename T>
const Vector3<T>
Vector3<T>::Zero = Vector3<T>(0,0,0);

template <typename T>
const Vector3<T>
Vector3<T>::UnitX = Vector3<T>(1,0,0);

template <typename T>
const Vector3<T>
Vector3<T>::UnitY = Vector3<T>(0,1,0);

template <typename T>
const Vector3<T>
Vector3<T>::UnitZ = Vector3<T>(0,0,1);

} // ::revel::math

//add an ifdef to set default 32 or 64 bit?
typedef math::Vector3<f32> vec3;

typedef math::Vector3<f32> vec3_f32;
typedef math::Vector3<f64> vec3_f64;
typedef math::Vector3<i32> vec3_i32;
typedef math::Vector3<u32> vec3_u32;
typedef math::Vector3<i16> vec3_i16;
typedef math::Vector3<u16> vec3_u16;
typedef math::Vector3<i8>  vec3_i8;
typedef math::Vector3<u8>  vec3_u8;


} // ::revel

#endif /* _RVL_VECTOR3_H_ */
