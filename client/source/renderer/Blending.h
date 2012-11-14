#ifndef BLENDING_H
#define BLENDING_H

#include "Color.h"

namespace revel
{
namespace renderer
{

enum class SourceBlendingFactor
{
    ZERO,
    ONE,
    SOURCE_ALPHA,
    ONE_MINUS_SOURCE_ALPHA,
    DESTINATION_ALPHA,
    ONE_MINUS_DESTINATION_ALPHA,
    DESTINATION_COLOR,
    ONE_MINUS_DESTINATION_COLOR,
    SOURCE_ALPHA_SATURATE,
    CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA
};

enum class DestinationBlendingFactor
{
    ZERO,
    ONE,
    SOURCE_COLOR,
    ONE_MINUS_SOURCE_COLOR,
    SOURCE_ALPHA,
    ONE_MINUS_SOURCE_ALPHA,
    DESTINATION_ALPHA,
    ONE_MINUS_DESTINATION_ALPHA,
    DESTINATION_COLOR,
    ONE_MINUS_DESTINATION_COLOR,
    CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA
};

enum class BlendEquation
{
    ADD,
    MINIMUM,
    MAXIMUM,
    SUBTRACT,
    REVERSE_SUBRACT
};

class Blending
{
    bool m_Enabled;
    SourceBlendingFactor m_SourceRGBFactor;
    SourceBlendingFactor m_SourceAlphaFactor;
    DestinationBlendingFactor m_DestinationRGBFactor;
    DestinationBlendingFactor m_DestinationAlphaFactor;
    BlendEquation m_RGBEquation;
    BlendEquation m_AlphaEquation;
    Color4<f32> m_Color;

public:
    Blending();

    bool is_enabled() const { return m_Enabled; }
    const  Color4<f32>& color() const { return m_Color; }
    SourceBlendingFactor src_rgb_factor() const { return m_SourceRGBFactor; }
    SourceBlendingFactor src_alpha_factor() const { return m_SourceAlphaFactor; }
    DestinationBlendingFactor dest_rgb_factor() const { return m_DestinationRGBFactor; }
    DestinationBlendingFactor dest_alpha_factor() const { return m_DestinationAlphaFactor; }
    BlendEquation rgb_equation() const { return m_RGBEquation; }
    BlendEquation alpha_equation() const { return m_AlphaEquation; }

    void enable(bool enable = true) { enable ? m_Enabled = true : m_Enabled = false; }
    void set_color(const  Color4<f32>& c) { m_Color = c; }
    void set_src_rgb_factor(SourceBlendingFactor factor) { m_SourceRGBFactor = factor; }
    void set_src_alpha_factor(SourceBlendingFactor factor) { m_SourceAlphaFactor = factor; }
    void set_dest_rgb_factor(DestinationBlendingFactor factor) { m_DestinationRGBFactor = factor; }
    void set_dest_alpha_factor(DestinationBlendingFactor factor) { m_DestinationAlphaFactor = factor; }
    void set_rgb_equation(BlendEquation eq) { m_RGBEquation = eq; }
    void set_alpha_equation(BlendEquation eq) { m_AlphaEquation = eq; }
};

} // ::revel::renderer
} // ::revel


#endif // BLENDING_H
