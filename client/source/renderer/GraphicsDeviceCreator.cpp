#include "GraphicsDeviceCreator.h"
#include "gl/GraphicsDeviceGL.h"

namespace revel
{
namespace renderer
{

GraphicsDeviceCreator::GraphicsDeviceCreator()
{
}

GraphicsDeviceCreator::~GraphicsDeviceCreator()
{
}

std::unique_ptr<GraphicsDevice>
GraphicsDeviceCreator::create_device(const std::string& api)
{
    if (api.compare("OpenGL") == 0)
        return std::unique_ptr<GraphicsDevice>(new gl::GraphicsDeviceGL());
    else
        return nullptr;
}

} // ::revel::renderer
} // ::revel
