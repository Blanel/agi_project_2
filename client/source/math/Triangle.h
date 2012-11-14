#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "math/Point3.h"
#include "math/Vector3.h"


namespace revel { namespace math
{

class Triangle
{
public:
    Triangle() {}
    Triangle(const point3& a, const point3& b, const point3& c)
        : vertices[0](a)
        , vertices[1](b)
        , vertices[2](c)
    {

    }

    vec3 getNormal() const
    {
        vec3 v1 = vertices[0] - vertices[1];
        vec3 v2 = vertices[2] - vertices[1];

        return (v1.cross(v2)).normalize();
    }

    point3 getCenter() const
    {
        point3 p(vertices[0].x + vertices[1].x + vertices[2].x,
                 vertices[0].y + vertices[1].y + vertices[2].y,
                 vertices[0].z + vertices[1].z + vertices[2].z);

        return p / 3.0f;
    }

    bool isValid() const
    {

    }


protected:
    point3 vertices[3];
};


}} // ::revel::math

#endif // TRIANGLE_H
