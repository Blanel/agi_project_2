#include "DepthRange.h"

namespace revel
{
namespace renderer
{


DepthRange::DepthRange(f32 near, f32 far)
    : m_Near(near)
    , m_Far(far)
{
}

f32
DepthRange::get_near() const
{
    return m_Near;
}

f32
DepthRange::get_far() const
{
    return m_Far;
}

void
DepthRange::set_near(f32 near)
{
    m_Near = near;
}

void
DepthRange::set_far(f32 far)
{
    m_Far = far;
}


} // ::revel::renderer
} // ::revel
