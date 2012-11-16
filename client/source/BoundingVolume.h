#ifndef BBOX_H
#define BBOX_H

#include "math/Point3.h"
#include "math/Vector3.h"
#include <limits>
#include <algorithm>

namespace revel
{

template <typename T>
class BoundingBox
{
    math::Point3<T> m_Min;
    math::Point3<T> m_Max;

public:
    BoundingBox()
        : m_Min(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity())
        , m_Max(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity())
    {
    }
    BoundingBox(const math::Point3<T>& p)
        : m_Min(p)
        , m_Max(p)
    {
    }
    BoundingBox(const math::Point3<T> &p1, const math::Point3<T> &p2)
        : m_Min(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z))
        , m_Max(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z))
    {
    }

    BoundingBox& expand(T delta)
    {
        m_Min.x -= delta;
        m_Min.y -= delta;
        m_Min.z -= delta;

        m_Max.x += delta;
        m_Max.y += delta;
        m_Max.z += delta;

        return *this;
    }

    const math::Point3<T>& p1() const
    {
        return m_Min;
    }

    math::Point3<T>& p1()
    {
        return m_Min;
    }

    const math::Point3<T>& p2() const
    {
        return m_Max;
    }

    math::Point3<T>& p2()
    {
        return m_Max;
    }

    T surface_area() const
    {
        vec3 d = (m_Max - m_Min);
        return 2.0f * (d.x * d.y + d.x * d.z + d.y * d.z);
    }

    T volume() const
    {
        vec3 d = (m_Max - m_Min);
        return d.x * d.y * d.z;
    }

    bool overlaps(const BoundingBox& b) const
    {
        bool x = (m_Max.x > b.m_Min.x) && (m_Min.x <= b.m_Max.x);
        bool y = (m_Max.y > b.m_Min.y) && (m_Min.y <= b.m_Max.y);
        bool z = (m_Max.z > b.m_Min.z) && (m_Min.z <= b.m_Max.z);

        return (x && y && z);
    }

    bool contains(const math::Point3<T>& p) const
    {
        bool x = (p.x > m_Min.x && p.x < m_Max.x);
        bool y = (p.y > m_Min.y && p.y < m_Max.y);
        bool z = (p.z > m_Min.z && p.z < m_Max.z);

        return (x && y && z);
    }
};

template <typename T>
class BoundingSphere
{
    math::Point3<T> m_CenterPoint;
    T m_Radius;

public:
    BoundingSphere()
        : m_CenterPoint(math::Point3<T>::Origin)
        , m_Radius(std::numeric_limits<T>::infinity())
    {

    }

    BoundingSphere(const math::Point3<T>& p, T radius)
        : m_CenterPoint(p)
        , m_Radius(radius)
    {

    }
};

typedef BoundingBox<f32>    BBox;
typedef BoundingBox<f32>    BBox_f32;
typedef BoundingBox<f64>    BBox_f64;

typedef BoundingSphere<f32> BSphere;
typedef BoundingSphere<f32> BSphere_f32;
typedef BoundingSphere<f64> BSphere_f64;

} // ::revel

#endif // BBOX_H
