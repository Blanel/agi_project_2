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
    point3 m_Position;
    point3 m_Target;

    math::quat m_Rotation;

    f32 m_XRot;
    f32 m_YRot;
    f32 m_ZRot;

    f32 m_Pitch;
    f32 m_Yaw;
    f32 m_Roll;
    
    vec3 m_Forward;
    vec3 m_Up;
    vec3 m_Right;

    f32 m_FieldOfView;
    f32 m_AspectRatio;
    f32 m_NearPlaneDistance;
    f32 m_FarPlaneDistance;

    math::mat4 m_View;
    math::mat4 m_Projection;


public:
    Camera();
    virtual ~Camera();

    const point3& position() const;
    void set_position(const point3& p);
    void set_position(f32 x, f32 y, f32 z);

    const point3& target() const;
    void set_target(const point3& target);
    void set_target(f32 x, f32 y, f32 z);

    f32 near_plane() const;
    void set_near_plane(f32 distance);
    f32 far_plane() const;
    void set_far_plane(f32 distance);

    f32 fov();
    void set_fov(f32 degrees);

    const vec3& up();
    const vec3& forward();
    const vec3& right();

    Camera& move_forward(f32 speed);

/*
    Camera& move_abs(f32 x, f32 y, f32 z) { position().x += x; m_Eye.y += y; m_Eye.z += z; }
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
        //return (math::Transform::translate(m_Position) * math::Transform::rotate_x(math::PI/6) * math::Transform::rotate_y(-math::PI/12)).inversed();
        return (math::Transform::rotate_x(math::PI/9) * math::Transform::translate(position())).inversed();
        return math::Transform::translate(position()).inversed();
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
        m_Projection = math::Transform::perspective(65.0f, 16.0/9.0, 0.5, 1500.0);
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
