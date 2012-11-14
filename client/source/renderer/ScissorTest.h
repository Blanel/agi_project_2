#ifndef SCISSORTEST_H
#define SCISSORTEST_H

#include "geo/Rectangle.h"

namespace revel
{
namespace renderer
{


class ScissorTest
{
    geo::Rect_f32 m_Rectangle;
    bool m_Enabled;

public:
    ScissorTest();

    bool is_enabled() const;
    const geo::Rect_f32& get_rectangle() const;

    void set_rectangle(const geo::Rect_f32& r);
    void enable(bool enable = true);

};

} // ::revel::renderer
} // ::revel

#endif // SCISSORTEST_H
