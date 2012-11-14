#ifndef DEVICE_H
#define DEVICE_H

#include <memory>
//#include "renderer/GraphicsDevice.h"

namespace revel
{

//forward decl
//namespace audio 	{ class AudioDevice; }
namespace renderer 	{ class GraphicsDevice; }

class Device
{
public:
	Device();

    static const std::unique_ptr<renderer::GraphicsDevice>& graphics();
    //static const std::unique_ptr<audio::AudioDevice>& audio();
    static void register_device(std::unique_ptr<renderer::GraphicsDevice>&& pDevice);
    //static void register_audio_device(std::unique_ptr<audio::AudioDevice>&& pDevice);

private:
    static std::unique_ptr<renderer::GraphicsDevice>    m_pGraphicsDevice;
    //static std::unique_ptr<audio::AudioDevice>          m_pAudioDevice;
};

} // ::revel

#endif // DEVICE_H
