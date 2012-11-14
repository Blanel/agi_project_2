#ifndef DEPTHTEST_H
#define DEPTHTEST_H

namespace revel
{
namespace renderer
{

enum class DepthTestFunction
{
    NEVER,
    NOT_EQUAL,
    LESS,
    LESS_THAN_OR_EQUAL,
    EQUAL,
    GREATER_THAN_OR_EQUAL,
    GREATER,
    ALWAYS
};

class DepthTest
{
    bool m_Enabled;
    DepthTestFunction m_Function;

public:
    DepthTest();

    void enable(bool enable = true) { enable ? m_Enabled = true : m_Enabled = false; }
    void set_depth_test_function(const DepthTestFunction& func) { m_Function = func; }

    bool is_enabled() const { return m_Enabled; }
    const DepthTestFunction& get_depth_test_function() const { return m_Function; }
};

} // ::revel::renderer
} // ::revel

#endif // DEPTHTEST_H
