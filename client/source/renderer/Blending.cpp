#include "Blending.h"

namespace revel
{
namespace renderer
{

Blending::Blending()
    : m_Enabled(false)
    , m_SourceRGBFactor(SourceBlendingFactor::ONE)
    , m_SourceAlphaFactor(SourceBlendingFactor::ONE)
    , m_DestinationRGBFactor(DestinationBlendingFactor::ZERO)
    , m_DestinationAlphaFactor(DestinationBlendingFactor::ZERO)
    , m_RGBEquation(BlendEquation::ADD)
    , m_AlphaEquation(BlendEquation::ADD)
    , m_Color(0, 0, 0, 0)
{

}

} // ::revel::renderer
} // ::revel

