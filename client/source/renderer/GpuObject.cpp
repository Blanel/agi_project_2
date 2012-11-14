#include "GpuObject.h"

namespace revel
{
namespace renderer
{

GpuObject::GpuObject()
    : m_Identifier(0)
{
}

GpuObject::~GpuObject()
{
}

u32
GpuObject::get_id() const
{
    return m_Identifier;
}

bool
GpuObject::is_valid() const
{
    return m_Identifier;
}


} // ::revel::renderer
} // ::revel
