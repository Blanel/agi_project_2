#ifndef DEPTHMASK_H
#define DEPTHMASK_H

namespace revel
{
namespace renderer
{

class DepthMask
{
    bool m_Enabled;
public:
    DepthMask();

    void enable(bool enable = true);
    bool is_enabled() const;
};

} // ::revel::renderer
} // ::revel

#endif // DEPTHMASK_H
