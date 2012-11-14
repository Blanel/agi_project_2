#include "Uniform.h"

namespace revel
{
namespace renderer
{

Uniform::Uniform(const std::string &name, UniformDatatype type)
    : m_Name(name)
    , m_Datatype(type)
{
}

Uniform::~Uniform()
{
}



}
}
