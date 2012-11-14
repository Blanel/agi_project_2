#ifndef PROGRAMPOINTSIZE_H
#define PROGRAMPOINTSIZE_H

#include "Types.h"

namespace revel
{
namespace renderer
{


class ProgramPointSize
{
    bool m_Enabled;
    f32 m_PointSize;

public:
    ProgramPointSize();

    bool is_enabled() const { return m_Enabled; }
    f32 point_size() const { return m_PointSize; }

    void enable(bool enabled = true) { enabled ? m_Enabled = true : m_Enabled = false; }
    void set_point_size(f32 s) { m_PointSize = s; }
};


} // ::revel::renderer
} // ::revel

#endif // PROGRAMPOINTSIZE_H
