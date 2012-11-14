#ifndef _RVL_POINT3_H_
#define _RVL_POINT3_H_

#include "../Types.h"
#include "Constants.h"

#include <cmath>

namespace revel { namespace math
{

// forward declarations
template <typename T> class Vector3;

template <typename T>
class Point3
{
public:
    Point3() : x(0), y(0), z(0) {}
    Point3(T x, T y, T z) : x(x), y(y), z(z) {}
    Point3(const Point3& p) : x(p.x), y(p.y), z(p.z) {}
    Point3(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z) {}
    ~Point3() {}
    
    /**
     * Assignment of a point
     *
     * @param p Input Point
     * @return Reference to itself
     */
	Point3& operator=(const Point3& p) 
    { 
        if (this != &p) 
        { 
            x = p.x; 
            y = p.y; 
            z = p.z; 
        } 
        return *this; 
    }
    
	Point3 lerp(const Point3&p, f32 t)
	{
		return (*this) * (1.0f - t) + p*t;
	}

    /**
	 * Equality comparison of two vectors.
	 *
	 * @param p Point
	 * @return True if the points are equal.
	 */
    bool operator==(const Point3& p)
    { 
        return (x == p.x && y == p.y && z == p.z); 
    }

    bool operator!=(const Point3& p)
    { 
        return !(*this == p);
    }

    /**
	 * Equality comparison of two points.
	 *
	 * @param p Point
     * @param epsilon Small number which is an acceptable bound. Predefined as 10^(-5).
	 * @return True if the points are equal.
	 */
    bool equal(const Point3& p, T epsilon = math::EPSILON) const
    { 
        return ((std::abs(x-p.x) > epsilon ||
                 std::abs(y-p.y) > epsilon ||
                 std::abs(z-p.z) > epsilon) ? 0 : 1);
    }
    
    /**
     * Addition of a vector to a point.
     *
     * @param v Input vector
     * @return Point in 2D space
     */
	Point3 operator+(Vector3<T>& v) const 
    { 
        return Point3(x + v.x, y + v.y, z + v.z); 
    }

    /**
     * Subtraction of a point from a point.
     *
     * @param v Input point
     * @return Vector in 3D space.
     */
    Vector3<T> operator-(const Point3& p) const
    { 
        return Vector3<T>(x - p.x, y - p.y, z - p.z); 
    }

    /**
     * Negation of point
     *
     */
    Point3 operator-() const
    {
        return Point3(-x, -y, -z);
    }
	
    /**
     * Array operator 
     *
     * @param x Index.
     * @return Reference to the element.
     */	
    T& operator[](i32 x) 
    { 
        return elem[x]; 
    }

    /**
     * Array operator 
     *
     * @param x Index.
     * @return Copy of the element.
     */	
    T operator[](i32 x) const 
    { 
        return elem[x]; 
    }
	
    /**
     * Get a pointer to the first element.
     *
     * @return The pointer.
     */    
    const T* get_ptr() const
    { 
        return elem; 
    }
	
    /**
     * Get a pointer to the first element.
     *
     * @return The pointer.
     */
    T* get_ptr()
    { 
        return elem; 
    }

	union
	{
		struct { T x, y, z; };
		T elem[3];
	};

    static const Point3<T> Origin;

};

template <typename T>
const Point3<T>
Point3<T>::Origin = Point3<T>(0, 0, 0);

}

    typedef math::Point3<f32> point3;

    typedef math::Point3<f32> point3_f32;
    typedef math::Point3<f64> point3_f64;

} // ::revel::math

#endif // _RVL_POINT3_H_
