#include "Device.h"

#include "renderer/GraphicsDevice.h"

namespace revel
{

Device::Device()
{

}

const std::unique_ptr<renderer::GraphicsDevice>&
Device::graphics()
{
    return m_pGraphicsDevice;
}

void
Device::register_device(std::unique_ptr<renderer::GraphicsDevice>&& pDevice)
{
    m_pGraphicsDevice = std::move(pDevice);
}


//std::unique_ptr<audio::AudioDevice> RDevice::m_pAudioDevice = nullptr;
std::unique_ptr<renderer::GraphicsDevice> Device::m_pGraphicsDevice = nullptr;

} // ::revel
