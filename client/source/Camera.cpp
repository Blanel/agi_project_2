#include "Camera.h"

namespace revel
{

Camera::Camera()
    : m_Position(0, 0, 1)
    , m_Target(0, 0, 0)
    , m_Rotation()
    , m_Forward(0, 0, -1)
    , m_Up(0, 1, 0)
    , m_Right(1, 0, 0)
    , m_FieldOfView(75)
    , m_AspectRatio(16.0/9.0)
    , m_NearPlaneDistance(0.1f)
    , m_FarPlaneDistance(1000.0f)
{
}

Camera::~Camera()
{
}

const point3& 
Camera::position() const 
{ 
    return m_Position; 
}

void 
Camera::set_position(const point3& p) 
{ 
    m_Position = p; 
}

void 
Camera::set_position(f32 x, f32 y, f32 z) 
{ 
    m_Position.x = x; m_Position.y = y; m_Position.z = z; 
}


const point3& 
Camera::target() const 
{ 
    return m_Target; 
}

void 
Camera::set_target(const point3& target) 
{ 
    m_Target = target; 
}

void 
Camera::set_target(f32 x, f32 y, f32 z) 
{ 
    m_Target.x = x; m_Target.y = y; m_Target.z = z; 
}

f32 
Camera::near_plane() const 
{ 
    return m_NearPlaneDistance; 
}

void 
Camera::set_near_plane(f32 distance) 
{ 
    m_NearPlaneDistance = distance; 
}

f32 
Camera::far_plane() const 
{ 
    return m_FarPlaneDistance; 
}

void 
Camera::set_far_plane(f32 distance) 
{ 
    m_FarPlaneDistance = distance; 
}

f32 
Camera::fov() 
{ 
    return m_FieldOfView; 
}

void 
Camera::set_fov(f32 degrees) 
{ 
    m_FieldOfView = degrees; 
}

const vec3& 
Camera::up() 
{ 
    return m_Up; 
}

const vec3& 
Camera::forward() 
{ 
    return m_Forward; 
}

const vec3& 
Camera::right() 
{ 
    return m_Right; 
}

Camera& 
Camera::move_forward(f32 speed)
{
    m_Position = (m_Position) + (m_Forward * speed);
}


/*
math::mat4
PerspectiveCamera::projection_matrix() const
{
    //f32 x = m_NearPlaneDistance * tan(math::deg_to_rad(m_FieldOfView) * 0.5f);
    //f32 y = x / m_AspectRatio;
    //f32 z = m_FarPlaneDistance - m_NearPlaneDistance;

    /*

    return math::mat4(
                        m_NearPlaneDistance / x, 0, 0, 0,
                        0, m_NearPlaneDistance / y, 0, 0,
                        0, 0, -(m_FarPlaneDistance + m_NearPlaneDistance)/ z, -2*(m_FarPlaneDistance * m_NearPlaneDistance)/z,
                        0, 0, -1, 0
                     );

    */
    /*
    return math::mat4(
                        m_NearPlaneDistance / x, 0, 0, 0,
                        0, m_NearPlaneDistance / y, 0, 0,
                        0, 0, -(m_FarPlaneDistance + m_NearPlaneDistance)/ z, -2*(m_FarPlaneDistance * m_NearPlaneDistance)/z,
                        0, 0, -1, 1
                     );

    */
//}

/*
math::mat4
OrthographicCamera::projection_matrix() const
{
    f32 x = m_NearPlaneDistance * tan(math::deg_to_rad(m_FieldOfView) * 0.5f);
    f32 y = x / m_AspectRatio;
    f32 z = m_FarPlaneDistance - m_NearPlaneDistance;

    return math::mat4::Identity;
}
*/


}
