#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "renderer/GpuObject.h"

namespace revel
{
namespace renderer
{

class Framebuffer : public GpuObject
{
public:
    Framebuffer() {}
    virtual ~Framebuffer() {}

    virtual void bind() = 0;
    virtual void unbind() = 0;
};

} // ::revel::renderer
} // ::revel

#endif // FRAMEBUFFER_H
