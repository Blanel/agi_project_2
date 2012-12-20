#ifndef _RVL_VECTOR2_H_
#define _RVL_VECTOR2_H_

#include "Types.h"
#include "math/Constants.h"
#include <cmath>

namespace revel { namespace math
{

template <typename T>
class Vector2
{
public:
	Vector2() {}
	Vector2(T a) 
        : x(a)
        , y(a) 
    {}
	Vector2(T ix, T iy) 
        : x(ix)
        , y(iy) 
    {}
	Vector2(const Vector2& v)
	{
		x = v.x;
		y = v.y;
	}
	Vector2(const T* p)
	{
		x = p[0];
		y = p[1];
	}
	~Vector2() {}

	/**
	 * Assignement of all variables in the vector.
	 *
	 * @param[in] ix X value.
     * @param[in] iy Y value.
     *
     * @return Reference to itself.
	 */
	Vector2&
	xy(T ix, T iy)
	{
		x = ix;
		y = iy;
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
	Vector2&
	operator=(const Vector2& v)
	{
		if (this != &v)
		{
			x = v.x; y = v.y;
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
    equal(const Vector2& v, T epsilon = EPSILON) const
	{
		return ((abs(x-v.x) > epsilon ||
                 abs(y-v.y) > epsilon) ? 0 : 1);                 
	}

   	/**
	 * Equality comparison of two vectors.
	 *
	 * @param v Vector
	 * @return True if vectors are equal.
	 */
	bool
	operator==(const Vector2& v) const
	{
		return (x == v.x && y == v.y);
	}

    /**
	 * Inequality comparison of two vectors.
	 *
	 * @param v Vector
	 * @return True if vectors are NOT equal.
	 */
	bool
	operator!=(const Vector2& v) const
	{
		return (!(*this == v));
	}

    /*
     * Negate a vector.
     * 
     * @return A negated vector
     */
	Vector2
	operator-() const
	{
		return Vector2(-x, -y);
	}

    /**
     * Vector addition.
     *
     * @param v Vector to add with.
     * @return Vector result.
     */
	Vector2
	operator+(const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}

    /**
     * Vector subtraction.
     *
     * @param v Vector to subtract with.
     * @return Vector result.
     */
	Vector2
	operator-(const Vector2& v) const
	{
		return Vector2(x - v.x, y - v.y);
	}

    /**
     * Vector multiplication.
     *
     * @param v Vector to multiply with.
     * @return Vector result.
     */
	Vector2
	operator*(const Vector2& v) const
	{
		return Vector2(x * v.x, y * v.y);
	}

    /**
     * Vector addition.
     *
     * @param v Vector to add with.
     * @return Reference to itself
     */
	Vector2&
	operator+=(const Vector2& v)
	{
		x += v.x; y += v.y;
		return *this;
	}

    /**
     * Vector subtraction.
     *
     * @param v Vector to subtract with.
     * @return Reference to itself
     */
	Vector2&
	operator-=(const Vector2& v)
	{
		x -= v.x; y -= v.y;
		return *this;
	}

    /**
     * Vector multiplication.
     *
     * @param v Vector to multiply with.
     * @return Reference to itself
     */
	Vector2&
	operator*=(const Vector2& v)
	{
		x*=v.x; y*=v.y;
		return *this;
	}

	bool
	operator<(const Vector2& v) const
	{
		if (x < v.x || (x == v.x && y < v.y))
			return true;
		else
			return false;
	}

    /**
     * Multiply vector elements with a scalar.
     *
     * @param a Scalar to multiply with.
     * @return Vector result.
     */
	Vector2
	operator*(T a) const
	{
		return Vector2(x*a, y*a);
	}

    /**
     * Divide vector elements with a scalar.
     *
     * @param a Scalar to multiply with.
     * @return Vector result.
     */
	Vector2
	operator/(T a) const
	{
		return Vector2(x/a, y/a);
	}

    /**
     * Multiply vector elements with a scalar.
     *
     * @param a Scalar to multiply with.
     * @return Reference to itself.
     */
	Vector2&
	operator*=(T a)
	{
		x*=a; y*= a;
		return *this;
	}

    /**
     * Divide vector elements with a scalar.
     *
     * @param a Scalar to divide with.
     * @return Reference to itself.
     */	
	Vector2&
	operator/=(T a)
	{
		x/=a; y*=a;
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
		return sqrt(x*x + y*y);
	}

    /**
     * Calculate the euclidean distance squared.
     *
     * @return Euclidean distance squared.
     */
	f32
	length_squared() const
	{
		return (x*x + y*y);
	}

    /**
     * Normalize a vector
     *
     * @return Normalized vector
     */
	Vector2
    normalized()
	{
		f32 n = 1/length();
        if (n <= 0) 
            n = 1;
       
        Vector2 res(this->x * n, this->y * n);
		return res;
	}

	union
	{
		struct { T x, y; };
		T elem[2];
	};
		
	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
};

/**
 * Normalize this vector vector
 *
 * @return Normalized vector
 */
template <typename T>
Vector2<T>&
normalized(Vector2<T>& v)
{
    f32 n = 1/v.length();
    if (n <= 0)
        n = 1;

    v.x*=n;
    v.y*=n;

    return v;
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
dot(const Vector2<T>& l, const Vector2<T>& r)
{
    return (l.x*r.x + l.y*r.y);
}

template <typename T>
const Vector2<T>
Vector2<T>::Zero = Vector2<T>(0,0);

template <typename T>
const Vector2<T>
Vector2<T>::UnitX = Vector2<T>(1,0);

template <typename T>
const Vector2<T>
Vector2<T>::UnitY = Vector2<T>(0,1);


} // ::revel::math


    typedef math::Vector2<f32> vec2;

    typedef math::Vector2<f32> vec2_f32;
    typedef math::Vector2<f64> vec2_f64;
    typedef math::Vector2<i32> vec2_i32;
    typedef math::Vector2<i32> ivec2;
    typedef math::Vector2<u32> vec2_u32;

} // ::revel

#endif // _RVL_VECTOR2_H_

