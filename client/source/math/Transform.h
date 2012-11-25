#ifndef _RVL_MATTRANSFORM_H_
#define _RVL_MATTRANSFORM_H_

#include "Types.h"
#include "math/RMath.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "math/Matrix4x4.h"
#include "math/Quaternion.h"

#include <cmath>

namespace revel { namespace math
{

template<typename T>
class MatrixTransform
{
public:
    static Matrix4x4<T> perspective(T angle, T aspect, T near, T far)
    {

        f32 size = near * tan(deg_to_rad(angle) * 0.5f);
        f32 right = size;
        f32 left = -right;
        f32 top = size / aspect;
        f32 bottom = -top;

        return Matrix4x4<T>(
                    2*near/(right - left), 			0, 						-(right + left)/(right - left), 	0,
                    0, 								2*near/(top - bottom), 	-(top + bottom)/(top - bottom), 	0,
                    0, 								0, 						-(far)/(far - near),				-(far * near)/(far - near),
                    0, 								0, 						-1, 								0);
    }

    static Matrix4x4<T> ortho(T left, T right, T bottom, T top, T near, T far)
	{
    	return Matrix4x4<T>(
    			2/(right-left), 	0, 					0, 				-(right+left)/(right-left),
    			0, 					2/(top - bottom), 	0, 				-(top+bottom)/(top-bottom),
    			0, 					0, 					-2/(far-near), 	-(far + near)/(far - near),
    			0, 					0, 					0, 				1);

	}

    /*
    static Matrix4x4<T> create_proj_matrix(f32 fovy, f32 aspect, f32 near, f32 far)
    {
        f32 a = tan(deg_to_rad(angle));

        f32 r = 1 / a * 1 / tan(fovy/2)
    }
    */

    /**
     * Construct a translation matrix.
     *
     * @param axis Translation vector.
     */
    static Matrix4x4<T> translate(const Vector3<T>& t)
    {
        return Matrix4x4<T>( 1, 0, 0, t.x,
                             0, 1, 0, t.y,
                             0, 0, 1, t.z,
                             0, 0, 0, 1 );
    }

    static Matrix4x4<T> look_at(const vec3& e, const vec3& p, const vec3& up)
    {
        vec3 c = (e - p).normalized();
        vec3 a = cross(up, c).normalized();
        vec3 b = cross(c, a);

        return Matrix4x4<T>( a.x, a.y, a.z, -dot(a, e),
                             b.x, b.y, b.z, -dot(b, e),
                             c.x, c.y, c.z, -dot(c, e),
                             0  , 0  , 0  , 1);

    }

    static Matrix4x4<T> translate(const Point3<T>& t)
    {
        return Matrix4x4<T>( 1, 0, 0, t.x,
                             0, 1, 0, t.y,
                             0, 0, 1, t.z,
                             0, 0, 0, 1 );
    }

    static Matrix4x4<T> translate(T x, T y, T z)
    {
        return Matrix4x4<T>( 1, 0, 0, x,
                             0, 1, 0, y,
                             0, 0, 1, z,
                             0, 0, 0, 1 );
    }

	/**
	 * Construct a rotation matrix for rotation around the x-axis
	 *
	 * @param r radians
	 */
    static Matrix4x4<T> rotate_x(T r)
	{
		return Matrix4x4<T>(
			1, 0, 0, 0,
			0, cosf(r), -sinf(r), 0,
			0, sinf(r), cosf(r), 0,
			0, 0, 0, 1
		);
	}

	/**
	 * Construct a rotation matrix for rotation around the y-axis
	 *
	 * @param r radians
	 */
    static Matrix4x4<T> rotate_y(T r)
	{
        return Matrix4x4<T>(
            cos(r), 0, sin(r), 0,
            0, 1, 0, 0,
			-sin(r), 0, cos(r), 0,
			0, 0, 0, 1
        );
	}

	/**
	 * Construct a rotation matrix for rotation around the z-axis
	 *
	 * @param r radians
	 */
    static Matrix4x4<T> rotate_z(T r)
	{
            return Matrix4x4<T>(
			cos(r), -sin(r), 0, 0,
			sin(r), cos(r), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
                        );
	}


    /**
     * Construct a rotation matrix.
     *
     * @param axis Axis to rotate around.
     * @param angle Degrees to rotate.
     */
    static Matrix4x4<T> rotate(const Vector3<T>& axis, f32 angle)
    {
        f32 c = cosf(angle);		
        f32 s = sinf(angle);

        return Matrix4x4<T>( 
            axis.x * axis.x + (1-axis.x * axis.x) * c,		                     
            axis.x * axis.y * (1-c) - axis.z * s,
            axis.x * axis.z * (1-c) + axis.y * s,
            0,
            axis.x * axis.y * (1-c) + axis.z * s,
            axis.y * axis.y + (1-axis.y * axis.y) * c,
            axis.y * axis.z * (1-c) - axis.x * s,
            0,
            axis.x * axis.z * (1-c) - axis.y * s,
            axis.y * axis.z * (1-c) + axis.x * s,
            axis.z * axis.z + (1-axis.z * axis.z) * c,
            0, 
            0, 
            0, 
            0, 
            1
        );        
    }

    /**
     * Construct a rotation matrix.
     *
     * @param q Unit quaternion which specifies a rotation.
     */
    static Matrix4x4<T> rotate(const Quaternion<T>& q)
    {
        return Matrix4x4<T>(
            1.0f - 2.0f * (q.y*q.y + q.z*q.z),	2.0f * (q.x*q.y + q.z*q.w),			2.0f * (q.x*q.z - q.y*q.w), 		0.0f,
            2.0f * (q.x*q.y - q.z*q.w), 		1.0f - 2.0f * (q.x*q.x + q.z*q.z),  2.0f * (q.z*q.y + q.x*q.w), 		0.0f,
            2.0f * (q.x*q.z + q.y*q.w),         2.0f * (q.y*q.z - q.x*q.w),         1.0f - 2.0f * (q.x*q.x + q.y*q.y),	0.0f,
            0.0f,								0.0f,					            0.0f,					            1.0f);
    }

    static Matrix4x4<T> scale(T sx, T sy, T sz)
    {
        return Matrix4x4<T>(
                    sx, 0, 0, 0,
                    0, sy, 0, 0,
                    0, 0, sz, 0,
                    0, 0, 0, 1);
    }

    static Matrix4x4<T> scale(T s)
    {
        return scale(s, s, s);
    }

    static Matrix4x4<T> scale(Vector3<T> v)
    {
        return scale(v.x, v.y, v.z);
    }
};

math::mat4
translate(const math::mat4& m, const vec3& v)
{
    return m * vec4(v, 1.0);
}

math::mat4
scale(const math::mat4& m, const vec3& s)
{
    return m * vec4(s, 1.0);
}

typedef MatrixTransform<f32> Transform;

}} // ::revel::math

#endif // _RVL_MATTRANSFORM_H_
