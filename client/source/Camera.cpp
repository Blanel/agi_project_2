#include "Camera.h"

namespace revel
{

Camera::Camera()
    : m_Eye(0, 0, 1)
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
