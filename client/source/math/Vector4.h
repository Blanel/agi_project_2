#ifndef _RVL_VECTOR4_H_
#define _RVL_VECTOR4_H_

#include "Types.h"
#include "math/Constants.h"
#include <cmath>

#include "math/Matrix4x4.h"

namespace revel { namespace math
{

//forward declarations
template <typename T> class Vector3;

/**
 * Templated vector with 4 dimensions.
 */
template <typename T>
class Vector4
{
public:
    Vector4() {}
    Vector4(T a) : x(a), y(a), z(a), w(a) {}
    Vector4(T ix, T iy, T iz, T iw) : x(ix), y(iy), z(iz), w(iw) {}
    Vector4(const Vector4& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
    }
    Vector4(const Vector3<T>& v, T a)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = a;
    }
    Vector4(const T* p)
    {
        x = p[0];
        y = p[1];
        z = p[2];
        w = p[3];
    }
    ~Vector4() {}

    /**
     * Assignement of all variables in the vector.
     *
     * @param[in] ix X value.
     * @param[in] iy Y value.
     * @param[in] iz Z value.
     * @param[in] iw W value.
     *
     * @return Reference to itself.
     */
    Vector4&
    xyzw(T ix, T iy, T iz, T iw)
    {
        x = ix;
        y = iy;
        z = iz;
        w = iw;

        return *this;
    }

    Vector3<T>
    xyz(void)
    {
        return Vector3<T>(x,y,z);
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
    Vector4&
    operator=(const Vector4& v)
    {
        if (this != &v)
        {
            x = v.x; y = v.y; z = v.z; w = v.w;
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
    equal(const Vector4& v, T epsilon = EPSILON) const
    {
        return ((abs(x-v.x) > epsilon ||
                 abs(y-v.y) > epsilon ||
                 abs(z-v.z) > epsilon || 
                 abs(w-v.w) > epsilon) ? 0 : 1);
    }



    /**
     * Equality comparison of two vectors.
     *
     * @param v Vector
     * @return True if vectors are equal.
     */
    bool
    operator==(const Vector4& v) const
    {
        return (x == v.x && y == v.y && z == v.z && w == v.w);
    }

    /**
     * Inequality comparison of two vectors.
     *
     * @param v Vector
     * @return True if vectors are NOT equal.
     */
    bool
    operator!=(const Vector4& v) const
    {
        return (!(*this == v));
    }

    /**
     * Negate a vector.
     * 
     * @return A negated vector
     */
    Vector4
    operator-() const
    {
        return Vector4(-x, -y, -z, -w);
    }

    /**
     * Vector addition.
     *
     * @param v Vector to add with.
     * @return Vector result.
     */
    Vector4
    operator+(const Vector4& v) const
    {
        return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
    }

    /**
     * Vector subtraction.
     *
     * @param v Vector to subtract with.
     * @return Vector result.
     */
	Vector4
    operator-(const Vector4& v) const
	{
		return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

    /**
     * Vector multiplication.
     *
     * @param v Vector to multiply with.
     * @return Vector result.
     */
	Vector4
    operator*(const Vector4& v) const
	{
		return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
	}

    /**
     * Vector addition.
     *
     * @param v Vector to add with.
     * @return Reference to itself
     */
	Vector4&
    operator+=(const Vector4& v)
	{
		x += v.x; y += v.y; z += v.z; w += v.w;
		return *this;
	}

    /**
     * Vector subtraction.
     *
     * @param v Vector to subtract with.
     * @return Reference to itself
     */
    Vector4&
    operator-=(const Vector4& v)
    {
        x -= v.x; y -= v.y; z -= v.z; w -= v.w;
        return *this;
    }

    /*
     * Vector multiplication.
     *
     * @param v Vector to multiply with.
     * @return Reference to itself
     */
    Vector4&
    operator*=(const Vector4& v)
    {
        x *= v.x; y *= v.y; z *= v.z; w *= v.w;
        return *this;
    }

    Vector4
    operator*(const Matrix4x4<T>& m) const
    {
        Vector4 res;

        res.x = x * m.e00 + y * m.e10 + z * m.e20 + w * m.e30;
        res.y = x * m.e01 + y * m.e11 + z * m.e21 + w * m.e31;
        res.z = x * m.e02 + y * m.e12 + z * m.e22 + w * m.e32;
        res.x = x * m.e03 + y * m.e13 + z * m.e23 + w * m.e33;

        return res;
    }

    /**
     * Multiply vector elements with a scalar.
     *
     * @param a Scalar to multiply with.
     * @return Vector result.
     */
    Vector4
    operator*(T a) const
    {
        return Vector4(x * a, y * a, z * a, w * a);
    }

    /**
     * Divide vector elements with a scalar.
     *
     * @param a Scalar to multiply with.
     * @return Vector result.
     */
    Vector4
    operator/(T a) const
    {
        return Vector4(x / a, y / a, z / a, w / a);
    }

    /**
     * Multiply vector elements with a scalar.
     *
     * @param a Scalar to multiply with.
     * @return Reference to itself.
     */	
    Vector4&
    operator*=(T a)
    {
        x *= a; y *= a; z *= a; w *= a;
        return *this;
    }

    /**
     * Divide vector elements with a scalar.
     *
     * @param a Scalar to divide with.
     * @return Reference to itself.
     */		
    Vector4&
    operator/=(T a)
    {
        x/=a; y*=a; z*=a; w*=a;
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
        return elem[x];
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
        return elem[x];
    }

    /**
     * Calculate the euclidean distance
     *
     * @return Euclidean distance.
     */
    f32
    length() const
    {
        return sqrt(x*x + y*y + z*z + w*w);
    }

    /**
     * Calculate the euclidean distance squared.
     *
     * @return Euclidean distance squared.
     */
    f32
    length_squared() const
    {
        return (x*x + y*y + z*z + w*w);
    }

    /**
     * Normalize a vector
     *
     * @return Normalized vector
     */
    Vector4
    normalized()
    {
        f32 n = 1/length();
        if (n <= 0)
            n = 1;

        Vector4 res(this->x * n, this->y * n, this->z * n, this->w * n);
        return res;
    }

    friend std::ostream& operator<<(std::ostream &os, const Vector4& v)
    {
        os << v.x << " \t" << v.y << " \t" << v.z << " \t" << v.w;

        return os;
    }

    union
    {
        struct { T x, y, z, w; };
        T elem[4];
    };

    static const Vector4 Zero;
    static const Vector4 UnitX;
    static const Vector4 UnitY;
    static const Vector4 UnitZ;
    static const Vector4 UnitW;
};

template <typename T, typename U>
Vector4<T> operator+(U val, const Vector4<T>& v)
{
    return Vector4<T>(v.x + val, v.y + val, v.z + val, v.w + val);
}

template <typename T, typename U>
Vector4<T> operator-(U val, const Vector4<T>& v)
{
    return Vector4<T>(v.x - val, v.y - val, v.z - val, v.w - val);
}

template <typename T>
Vector4<T>&
normalize(Vector4<T>& v)
{
    f32 n = 1/v.length();
    if (n <= 0)
        n = 1;

    v.x *= n;
    v.y *= n;
    v.z *= n;
    v.w *= n;;

    return v;
}

template <typename T>
Vector4<T>&
normalize(Vector4<T>&& v)
{
    return normalize(std::ref(v));
}


/**
 * Calculate the dot product between two vectors
 *
 * @param l Input vector (lhs)
 * @param r Input vector (rhs)
 * @return Scalar with the dot product
 */
template <typename T>
T
dot(const Vector4<T>& l, const Vector4<T>& r)
{
    return (l.x*r.x + l.y*r.y + l.z*r.z + l.w*r.w);
}


/*
template <typename T, typename U>
Vector4<U> operator*(const Vector4<U>& v, const Matrix4x4<T>& m)
{
    Vector4<U> res;

    res.x = v.x * m.e00 + v.y * m.e10 + v.z * m.e20 + v.w * m.e30;
    res.y = v.x * m.e01 + v.y * m.e11 + v.z * m.e21 + v.w * m.e31;
    res.z = v.x * m.e02 + v.y * m.e12 + v.z * m.e22 + v.w * m.e32;
    res.x = v.x * m.e03 + v.y * m.e13 + v.z * m.e23 + v.w * m.e33;

    return res;
}

template <typename T, typename U>
Vector4<U>& operator*=(const Vector4<U>& v, const Matrix4x4<T>& m)
{
    Vector4<U> res;

    res.x = v.x * m.e00 + v.y * m.e10 + v.z * m.e20 + v.w * m.e30;
    res.y = v.x * m.e01 + v.y * m.e11 + v.z * m.e21 + v.w * m.e31;
    res.z = v.x * m.e02 + v.y * m.e12 + v.z * m.e22 + v.w * m.e32;
    res.x = v.x * m.e03 + v.y * m.e13 + v.z * m.e23 + v.w * m.e33;

    v = res;
    return v;
}
*/

template <typename T>
const Vector4<T>
Vector4<T>::Zero = Vector4<T>(0,0,0,0);

template <typename T>
const Vector4<T>
Vector4<T>::UnitX = Vector4<T>(1,0,0,0);

template <typename T>
const Vector4<T>
Vector4<T>::UnitY = Vector4<T>(0,1,0,0);

template <typename T>
const Vector4<T>
Vector4<T>::UnitZ = Vector4<T>(0,0,1,0);

template <typename T>
const Vector4<T>
Vector4<T>::UnitW = Vector4<T>(0,0,0,1);

} // ::revel::math

typedef math::Vector4<f32> vec4;
typedef math::Vector4<f32> vec4_f32;
typedef math::Vector4<f64> vec4_f64;
typedef math::Vector4<i32> vec4_i32;
typedef math::Vector4<u32> vec4_u32;

} // ::revel

#endif /* _RVL_VECTOR4_H_ */
