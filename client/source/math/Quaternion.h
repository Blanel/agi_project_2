#ifndef _RVL_QUATERNION_H_
#define _RVL_QUATERNION_H_

#include <cmath>
#include "Types.h"
#include "Vector3.h"
#include "Matrix4x4.h"

namespace revel 
{ 
namespace math
{

template <typename T> class Vector3;

template <typename T>
class Quaternion
{
public:
	Quaternion() : x(0), y(0), z(0), w(1) {}
	Quaternion(T a, T b, T c, T d) : x(a), y(b), z(c), w(d) {}
	Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
	Quaternion(const Vector3<T>& v, T a) : x(v.x), y(v.y), z(v.z), w(a) {}
	Quaternion(const Matrix4x4<T>& m)
	{
		f32 t = m.trace();

		if (t > 0)
		{
			f32 s = 0.5f / sqrt(t);

			x = (m.e21 - m.e12) * s;
			y = (m.e02 - m.e20) * s;
			z = (m.e10 - m.e01) * s;
			w = 0.25 / s;
		}
		else
		{
			if (m.e00 > m.e11 && m.e00 > m.e22)
			{
				f32 s = sqrtf(1.0 + m.e00 - m.e11 - m.e22) * 2.0f;

				x = 0.5 / s;
				y = (m.e01 * m.e10) / s;
				z = (m.e02 * m.e20) / s;
				w = (m.e12 * m.e21) / s;
			}
			else if (m.e11 > m.e22)
			{
				f32 s = sqrtf(1.0f + m.e11 - m.e00 - m.e22) * 2.0f;

				x = (m.e01 + m.e10) / s;
				y = 0.5 / s;
				z = (m.e12 + m.e21) / s;
				w = (m.e02 + m.e20) / s;
			}
			else
			{
				f32 s = sqrtf(1.0f + m.e22 - m.e00 - m.e11) * 2.0f;

				x = (m.e02 + m.e20) / s;
				y = (m.e12 + m.e21) / s;
				z = 0.5 / s;
				w = (m.e01 + m.e10) / s;
			}
		}
	}

    static Quaternion from_axis_angle(const Vector3<T>& axis, T angle)
	{
        f32 sina;

        angle *= 0.5f;
        Vector3<T> vn(axis.normalized());

        sina = sin(angle);

        return Quaternion(vn.x * sina, vn.y * sina, vn.z * sina, cos(angle));
	}

    static Quaternion from_euler(T roll, T pitch, T yaw)
	{
        //borrowed this from the XNA framework
        Quaternion quaternion;

        float num9 = roll * 0.5f;
        float num6 = (float) sinf((double) num9);
        float num5 = (float) cosf((double) num9);
        float num8 = pitch * 0.5f;
        float num4 = (float) sinf((double) num8);
        float num3 = (float) cosf((double) num8);
        float num7 = yaw * 0.5f;
        float num2 = (float) sinf((double) num7);
        float num = (float) cosf((double) num7);

        quaternion.x = ((num * num4) * num5) + ((num2 * num3) * num6);
        quaternion.y = ((num2 * num3) * num5) - ((num * num4) * num6);
        quaternion.z = ((num * num3) * num6) - ((num2 * num4) * num5);
        quaternion.w = ((num * num3) * num5) + ((num2 * num4) * num6);

        return quaternion;
	}

    f32 roll() const
    {
        return atan2(2*(x*y + w*z), w*w + x*x - y*y - z*z);
    }

    f32 pitch() const
    {
        return atan2(2*(y*z + w*x), w*w - x*x - y*y + z*z);
    }

    f32 yaw() const
    {
        return asin(-2*(x*z - w*y));
    }

    void axis_angle(Vector3<T>& axis, f32& angle)
	{
		f32 scale = this->length();

		axis.x = x / scale;
		axis.y = y / scale;
		axis.z = z / scale;

		angle = acos(w) * 2.0f;
	}

    Quaternion& invert()
    {
        x = -x;
        y = -y;
        z = -z;

        //Probably a good idea to normalize here.
        normalize();

        return *this;
    }

    Quaternion inverse() const
    {
        Quaternion q(*this);
        return q.invert();
    }

	f32 length() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

    Quaternion& normalize(T epsilon = math::EPSILON)
	{
        f32 mag2 = (x * x + y * y + z * z + w * w);

        if (fabs(mag2 - 1.0f) > epsilon)
        {
            f32 l = 1 / sqrt(mag2);

            x *= l;
            y *= l;
            z *= l;
            w *= l;
        }

		return *this;
	}

	Quaternion conjugate() const
	{
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion operator*(const Quaternion& q) const
	{
		return Quaternion(
				w * q.x + x * q.w + y * q.z - z * q.y,
				w * q.y - x * q.z + y * q.w + z * q.x,
				w * q.z + x * q.y - y * q.x + z * q.w,
				w * q.w - x * q.x - y * q.y - z * q.z
		);
	}

	Vector3<T> operator*(const Vector3<T>& v) const
	{
        Vector3<T> vn(v.normalized());

        Quaternion vq(vn.x, vn.y, vn.z, 0.0);
        Quaternion rq;

		rq = vq * this->conjugate();
		rq = *this * rq;

		return Vector3<T>(rq.x, rq.y, rq.z);
	}

	T x, y, z, w;

	static const Quaternion Identity;
};

template <typename T>
const Quaternion<T>
Quaternion<T>::Identity = Quaternion<T>(0.0, 0.0, 0.0, 1.0);

typedef Quaternion<f32> quat;

typedef Quaternion<f32> quat_f32;
typedef Quaternion<f64> quat_f64;

} // ::revel::math
} // ::revel

#endif /* _RVL_QUATERNION_H_ */

