#ifndef GPURESOURCE_H_
#define GPURESOURCE_H_

#include "Types.h"
#include <GL/glew.h>
#include "GpuException.h"
#include "Log.h"

namespace revel
{
namespace renderer
{

class GpuObject
{
public:
    GpuObject();
    virtual ~GpuObject();

    u32 get_id() const;
    bool is_valid() const;

protected:
    u32 m_Identifier;
};

} // ::revel::renderer
} // ::revel

#endif // GPURESOURCE_H_
