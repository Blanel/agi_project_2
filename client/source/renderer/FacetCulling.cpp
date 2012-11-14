#include "FacetCulling.h"

namespace revel
{
namespace renderer
{

FacetCulling::FacetCulling()
{
}

const CullFace&
FacetCulling::cull_face() const
{
    return m_CullFace;
}

const WindingOrder&
FacetCulling::winding_order() const
{
    return m_FrontFaceWindingOrder;
}

bool
FacetCulling::is_enabled() const
{
    return m_Enabled;
}

void
FacetCulling::enable(bool enable)
{
    enable ? m_Enabled = true : m_Enabled = false;
}

void
FacetCulling::set_cull_face(CullFace cullface)
{
    m_CullFace = cullface;
}

void
FacetCulling::set_winding_order(WindingOrder order)
{
    m_FrontFaceWindingOrder = order;
}

} // ::revel::renderer
} // ::revel
