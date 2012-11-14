#include "DepthMask.h"

namespace revel
{
namespace renderer
{


DepthMask::DepthMask()
{
}

void
DepthMask::enable(bool enable)
{
    enable ? m_Enabled = true : m_Enabled = false;
}

bool
DepthMask::is_enabled() const
{
    return m_Enabled;
}

} // ::revel::renderer
} // ::revel
