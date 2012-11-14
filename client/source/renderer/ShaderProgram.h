#ifndef GPUPROGRAM_H
#define GPUPROGRAM_H

#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

#include "renderer/GpuObject.h"
#include "renderer/ShaderVertexAttrib.h"
#include "renderer/FragmentOutput.h"
#include "renderer/Uniform.h"

namespace revel
{
namespace renderer
{

class ShaderProgram : public GpuObject
{
public:
    ShaderProgram();
    virtual ~ShaderProgram();

    virtual void use() = 0;
    //virtual void unbind() = 0;


    /**
     * @brief Find a vertex attribute in the shader program.
     */
    const ShaderVertexAttrib& vertex_attrib(const std::string& name)
    {
        auto it = m_Attributes.find(name);

        if (it != m_Attributes.end())
        {
            return it->second;
        }

        else throw GpuException("Invalid vertex attribute");
    }    

    const std::unique_ptr<FragmentOutput>& fragment_output(const std::string& name)
    {

    }

    /**
     * @brief Find a uniform in the shader program.
     */
    template <typename T>
    UniformT<T>& uniform(const std::string& name)
    {
        auto it = m_Uniforms.find(name);

        if (it != m_Uniforms.end())
        {
            return *reinterpret_cast<UniformT<T>*>(it->second.get());
        }

        else throw GpuException("Invalid uniform name");
    }

protected:
    std::map<std::string, std::unique_ptr<Uniform>> m_Uniforms;
    std::map<std::string, ShaderVertexAttrib> m_Attributes;

    std::vector<std::unique_ptr<FragmentOutput>> m_FragmentOutputs;


    const std::string m_VertexShaderSource;
    const std::string m_FragmentShaderSource;
    const std::string m_GeometryShaderSource;

};

} // ::revel::renderer
} // ::revel

#endif // GPUPROGRAM_H
