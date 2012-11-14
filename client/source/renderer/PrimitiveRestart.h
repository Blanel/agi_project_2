#ifndef PRIMITIVERESTART_H
#define PRIMITIVERESTART_H

#include "Types.h"

namespace revel
{
namespace renderer
{

class PrimitiveRestart
{
    bool m_Enabled;
    i32 m_Index;

public:
    PrimitiveRestart();

    bool is_enabled() const { return m_Enabled; }
    i32 index() const { return m_Index; }

    void enable(bool enable) { enable ? m_Enabled = true : m_Enabled = false; }
    void set_index(u32 x) { m_Index = x; }

};

} // ::revel::renderer
} // ::revel

#endif // PRIMITIVERESTART_H
