#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "math/Point2.h"
#include "math/Vector2.h"

namespace revel
{

namespace geo
{

template <typename T>
class Rectangle
{
public:
    Rectangle()
    {

    }

    Rectangle(const math::Point2<T>& p1, const math::Point2<T>& p2)
        : m_P1(p1)
        , m_P2(p2)
    {

    }

    Rectangle(const math::Point2<T>& p1, T width, T height)
        : m_P1(p1)
        , m_P2(p1.x + width, p1.y + height)
    {

    }

    math::Point2<T>& p1()
    {
        return m_P1;
    }

    math::Point2<T>& p2()
    {
        return m_P2;
    }

    const math::Point2<T>& p1() const
    {
        return m_P1;
    }

    const math::Point2<T>& p2() const
    {
        return m_P2;
    }

    T width() const
    {
        math::Point2<T> p =  m_P2 - m_P1;
        return p.x;
    }

    T height() const
    {
        math::Point2<T> p =  m_P2 - m_P1;
        return p.y;
    }

    T area() const
    {
        math::Point2<T> p =  m_P2 - m_P1;
        return p.x * p.y;
    }

    bool contains(const math::Point2<T>& p) const
    {
        return (p.x >= m_P1.x && p.y >= m_P1.y && p.x <= m_P2.x && p.y <= m_P2.y);
    }

    Rectangle& operator+(const math::Point2<T>& p)
    {
        m_P1 += p;
        m_P2 += p;

        return *this;
    }

    Rectangle& operator+(const math::Vector2<T>& v)
    {
        m_P1 += v;
        m_P2 += v;

        return *this;
    }

protected:
    math::Point2<T> m_P1;
    math::Point2<T> m_P2;
};

typedef Rectangle<f32> Rect_f32;
typedef Rectangle<u32> Rect_u32;
typedef Rectangle<i32> Rect_i32;


} // ::revel::geo

} // ::revel

#endif // RECTANGLE_H_
