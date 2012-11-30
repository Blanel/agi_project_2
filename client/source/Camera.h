#ifndef CAMERA_H
#define CAMERA_H

#include "math/Point3.h"
#include "math/Vector3.h"
#include "math/Matrix3x3.h"
#include "math/Matrix4x4.h"
#include "math/Quaternion.h"
#include "math/RMath.h"
#include "math/Transform.h"

namespace revel
{

class Camera
{
protected:
    point3 m_Eye;
    point3 m_Target;

    math::quat m_Rotation;

    vec3 m_Forward;
    vec3 m_Up;
    vec3 m_Right;

    f32 m_FieldOfView;
    f32 m_AspectRatio;
    f32 m_NearPlaneDistance;
    f32 m_FarPlaneDistance;

    math::mat4 m_Projection;

public:
    Camera();
    virtual ~Camera();

    const point3& eye() const { return m_Eye; }
    void set_eye(const point3& p) { m_Eye = p; }
    void set_eye(f32 x, f32 y, f32 z) { m_Eye.x = x; m_Eye.y = y; m_Eye.z = z; }

    const point3& target() const { return m_Target; }
    void set_target(const point3& target) { m_Target = target; }
    void set_target(f32 x, f32 y, f32 z) { m_Target.x = x; m_Target.y = y; m_Target.z = z; }

    void set_near_plane(f32 distance) { m_NearPlaneDistance = distance; }
    void set_far_plane(f32 distance) { m_FarPlaneDistance = distance; }

    f32 near_plane() const { return m_NearPlaneDistance; }
    f32 far_plane() const { return m_FarPlaneDistance; }

    f32 fov() { return m_FieldOfView; }
    void set_fov(f32 degrees) { m_FieldOfView = degrees; }

    const vec3& up() { return m_Up; }
    const vec3& forward() { return m_Forward; }
    const vec3& right() { return m_Right; }

/*
    Camera& move_abs(f32 x, f32 y, f32 z) { m_Eye.x += x; m_Eye.y += y; m_Eye.z += z; }
    Camera& move_rel(f32 x, f32 y, f32 z) { m_Eye.x += x; m_Eye.y += y; m_Eye.z += z; }

    Camera& rotate_x(f32 radians)
    {
        m_Rotation = math::quat(vec3(1, 0, 0), radians) * m_Rotation;
    }
*/

    const math::mat4& projection_matrix() const 
    {
        return m_Projection;
    }

    math::mat4 view_matrix()
    {
        //return look_at(m_Eye, m_Target, m_Up).inversed();
        return (math::Transform::translate(m_Eye) * math::Transform::rotate_x(math::PI/18)).inversed();
        //return (math::Transform::rotate_x(math::PI/3) * math::Transform::translate(m_Eye)).inversed();
    }

    math::mat4 look_at(point3 eye, point3 target, vec3 up = vec3(0, 1, 0))
    {
        vec3 campos(eye);

        math::normalize(up);

        vec3 forward = target - eye;
        math::normalize(forward);

        vec3 right = math::cross(forward, up);
        math::normalize(right);

        math::mat4 m(right.x, up.x, forward.x, -dot(right, campos),
                     right.y, up.y, forward.y, -dot(up, campos),
                     right.z, up.z, forward.z, -dot(forward, campos),
                     0,       0,    0,         1);

        return m;
    }
};


class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera()
    {
        m_Projection = math::Transform::perspective(60.0f, 16.0/9.0, 0.1, 1000.0);
    }
};

/*
class OrthographicCamera : public Camera
{
public:
    OrthographicCamera()
    {

    }

    math::mat4 projection_matrix() const;
};
*/


}

#endif // CAMERA_H
