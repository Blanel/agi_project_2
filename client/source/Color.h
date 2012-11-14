#ifndef COLOR_H
#define COLOR_H

#include "Types.h"

namespace revel
{

template <typename T>
class Color4
{
    T m_Red;
    T m_Green;
    T m_Blue;
    T m_Alpha;

public:
    Color4()
    {}
    Color4(T r, T g, T b, T a)
        : m_Red(r)
        , m_Green(g)
        , m_Blue(b)
        , m_Alpha(a)
    {}

    const T& r() const { return m_Red; }
    const T& g() const { return m_Green; }
    const T& b() const { return m_Blue; }
    const T& a() const { return m_Alpha; }

    void r(T r) { m_Red = r; }
    void g(T g) { m_Green = g; }
    void b(T b) { m_Blue = b; }
    void a(T a) { m_Alpha = a; }

    /*
    static Color4 Black;
    static Color4 White;

    static Color4 Red;
    static Color4 Green;
    static Color4 Blue;
    */
};

typedef Color4<u8> Color4_u8;
typedef Color4<f32> Color4_f32;

//} // ::revel::img

/*
template <typename T>
Color4 Color4<T>::Black = Color(0, 0, 0, 255);
template <typename T>
Color4 Color4<T>::White = Color(255, 255, 255, 255);
template <typename T>
Color4 Color4<T>::Red = Color(255, 0, 0, 255);
template <typename T>
Color4 Color4<T>::Blue = Color(0, 255, 0, 255);
template <typename T>
Color4 Color4<T>::Green = Color(0, 0, 255, 255);
*/

} // ::revel

#endif // COLOR_H
