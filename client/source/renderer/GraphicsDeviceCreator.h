#ifndef GRAPHICSDEVICECREATOR_H_
#define GRAPHICSDEVICECREATOR_H_

#include <memory>
#include <string>

namespace revel
{
namespace renderer
{

//forward decl
class GraphicsDevice;

class GraphicsDeviceCreator
{
public:
    GraphicsDeviceCreator();
    ~GraphicsDeviceCreator();

    /**
     * @brief Create a render device.
     *
     * @param api The API (OpenGL / DirectX) used by the device.
     */
    static std::unique_ptr<GraphicsDevice> create_device(const std::string& api);
};

} // ::revel::renderer
} // ::revel

#endif // GRAPHICSDEVICECREATOR_H_
