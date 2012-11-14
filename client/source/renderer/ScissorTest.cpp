#include "ScissorTest.h"

namespace revel
{
namespace renderer
{

ScissorTest::ScissorTest()
    : m_Rectangle(math::point2::Origin, 0, 0)
    , m_Enabled(false)
{
}

const geo::Rect_f32&
ScissorTest::get_rectangle() const
{
    return m_Rectangle;
}

void
ScissorTest::enable(bool enable)
{
    enable ? m_Enabled = true : m_Enabled = false;
}

void
ScissorTest::set_rectangle(const geo::Rect_f32& r)
{
    m_Rectangle = r;
}


} // ::revel::renderer
} // ::revel
