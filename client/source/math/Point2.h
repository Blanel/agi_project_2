#ifndef POINT2_H_
#define POINT2_H_

#include "Types.h"
#include "Constants.h"

namespace revel { namespace math
{

// forward declarations
template <class T> class Vector2;

template <class T> class Point2
{
public:
    Point2() : x(0), y(0) {}
    Point2(T x, T y) : x(x), y(y) {}
    Point2(const Point2& p) : x(p.x), y(p.y) {}
    Point2(const Vector2<T>& v) : x(v.x), y(v.y) {}
    ~Point2() {}
    
    void set(T x, T y) { this->x=x; this->y=y; }

    /**
     * Assignment of a point
     *
     * @param p Input Point
     * @return Reference to itself
     */
    Point2& operator=(const Point2& p)
    { 
        if (this != &p) 
        { 
            x = p.x; 
            y = p.y; 
        } 
        return *this; 
    }

    /**
     * Equality comparison of two points.
     *
     * @param p Point
     * @return True if the points are equal.
     */
    bool operator==(const Point2& p) const
    { 
        return (x == p.x && y == p.y); 
    }

    /**
     * Equality comparison of two points.
     *
     * @param p Point
     * @param epsilon Small number which is an acceptable bound. Predefined as 10^(-5).
     * @return True if the points are equal.
     */
    bool equal(const Point2& p, T epsilon = EPSILON) const
    { 
        return (abs(x-p.x) > epsilon || abs(y-p.y) > epsilon) ? 0 : 1;
    }

    /**
     * Addition of a vector to a point.
     *
     * @param v Input vector
     * @return Point in 2D space
     */
    Point2 operator+(Vector2<T>& v) const
    { 
        return Point2(x + v.x, y + v.y); 
    }

    /**
     * Addition of a point to a point.
     *
     * @param v Input vector
     * @return Point in 2D space
     */
    Point2<T> operator+(const Point2<T>& p) const
    { 
        return Point2<T>(x + p.x, y + p.y); 
    }


    /**
     * Subtraction of a point from a point.
     *
     * @param v Input point
     * @return Vector in 2D space.
     */
    Vector2<T> operator-(Point2& p) const 
    { 
        return Vector2<T>(x - p.x, y - p.y); 
    }

    /**
     * Array operator 
     *
     * @param x Index.
     * @return Reference to the element.
     */	
    T& operator[](i32 x) { return elem[x]; }

    /**
     * Array operator 
     *
     * @param x Index.
     * @return Copy of the element.
     */	
    T operator[](i32 x) const { return elem[x]; }

    /**
     * Get a pointer to the first element.
     *
     * @return The pointer.
     */
    const T* get_ptr() const { return elem; }
    
    /**
     * Get a pointer to the first element.
     *
     * @return The pointer.
     */
    T* get_ptr() { return elem; }

    union
    {
        struct { T x, y; };
        T elem[2];
    };

    static const Point2<T> Origin;
};


template <typename T>
const Point2<T>
Point2<T>::Origin = Point2<T>(0, 0);

typedef Point2<f32> point2;

typedef Point2<i32> point2_i32;
typedef Point2<u32> point2_u32;
typedef Point2<f32> point2_f32;
typedef Point2<f64> point2_f64;

}} // ::revel::math

#endif // _RVL_POINT2_H_ 
