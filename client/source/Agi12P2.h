#ifndef AGI12_RENDERCLIENT_H_
#define AGI12_RENDERCLIENT_H_

#include <cassert>
#include <memory>
#include <stack>
#include <map>

#include "renderer/GraphicsDevice.h"
#include "renderer/GraphicsWindow.h"

namespace revel
{

class AGI12_RenderClient
{        
protected:
    bool                        				m_Running;
    std::shared_ptr<renderer::GraphicsWindow>   m_pWindow;

public:
    Project2();
    ~Project2();

    u32 run();
    void quit();

    const std::shared_ptr<renderer::GraphicsWindow>& active_window();

protected:

    virtual void poll_system_events() = 0;
};

}

#endif // AGI12_RENDERCLIENT_H_
