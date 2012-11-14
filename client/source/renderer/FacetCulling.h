#ifndef FACETCULLING_H
#define FACETCULLING_H

#include "renderer/WindingOrder.h"

namespace revel
{
namespace renderer
{

enum class CullFace
{
    FRONT,
    BACK,
    FRONT_AND_BACK
};

class FacetCulling
{
    bool m_Enabled;
    CullFace m_CullFace;
    WindingOrder m_FrontFaceWindingOrder;

public:
    FacetCulling();

    bool is_enabled() const;
    const CullFace& cull_face() const;
    const WindingOrder& winding_order() const;

    void enable(bool enable = true);
    void set_cull_face(CullFace cullface);
    void set_winding_order(WindingOrder order);
};

} // ::revel::renderer
} // ::revel

#endif // FACETCULLING_H
