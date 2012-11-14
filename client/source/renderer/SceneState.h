#ifndef SCENESTATE_H
#define SCENESTATE_H

#include <memory>

#include "Types.h"
#include "Camera.h"

#include "math/Matrix4x4.h"

//#include <glm/glm.h>

namespace revel
{

class Camera;

namespace renderer
{

class SceneState
{
protected:
    f32 m_DiffuseIntensity;
    f32 m_SpecularIntensity;
    f32 m_AmbientIntensity;
    f32 m_Shininess;

    math::mat4 m_ModelMatrix;
    math::mat4 m_ViewMatrix;
    math::mat4 m_ModelViewMatrix;
    math::mat4 m_ProjectionMatrix;
    math::mat4 m_ModelViewProjectionMatrix;

    std::shared_ptr<Camera> m_pCamera;

public:
    SceneState();

    const math::mat4& model_matrix() const
    {
        return m_ModelMatrix;
    }

    const math::mat4& view_matrix() const
    {
        return m_ViewMatrix;
    }

    const math::mat4& projection_matrix() const
    {
        return m_ProjectionMatrix;
    }

    const math::mat4& model_view_matrix() const
    {
        return m_ModelViewMatrix;
    }

    const math::mat4& mvp_matrix() const
    {
        return m_ModelViewProjectionMatrix;
    }

    void set_world_matrix(const math::mat4& m)
    {
        m_ModelMatrix = m;
    }

    void set_view_matrix(const math::mat4& m)
    {
        m_ViewMatrix = m;
    }

    void set_projection_matrix(const math::mat4& m)
    {
        m_ProjectionMatrix = m;
    }

    void set_model_view_matrix(const math::mat4& m)
    {
        m_ModelViewMatrix = m;
    }

    void set_model_view_proj_matrix(const math::mat4& m)
    {
        m_ModelViewProjectionMatrix = m;
    }

    const std::shared_ptr<Camera>& camera()
    {
        return m_pCamera;
    }

    void set_camera(const std::shared_ptr<revel::Camera>& cam)
    {
        m_pCamera = cam;
    }

};

}
}

#endif // SCENESTATE_H
