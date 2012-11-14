#ifndef DEPTHRANGE_H
#define DEPTHRANGE_H

#include "Types.h"

namespace revel
{
namespace renderer
{


class DepthRange
{
    f32 m_Near;
    f32 m_Far;
public:
    DepthRange(f32 near = 0.0, f32 far = 1.0);

    f32 near() const;
    f32 far() const;

    void set_near(f32 near);
    void set_far(f32 far);
};

} // ::revel::renderer
} // ::revel

#endif // DEPTHRANGE_H
