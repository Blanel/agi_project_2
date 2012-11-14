#include "DepthTest.h"

namespace revel
{
namespace renderer
{

DepthTest::DepthTest()
    : m_Enabled(true)
    , m_Function(DepthTestFunction::LESS)
{
}

} // ::revel::renderer
} // ::revel
