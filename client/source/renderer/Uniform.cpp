#include "Uniform.h"

namespace revel
{
namespace renderer
{

UniformBase::UniformBase(const std::string& name, UniformDatatype type)
	: m_Name(name)
	, m_Datatype(type)
{

}

UniformBase::~UniformBase()
{

}

UniformDatatype 
UniformBase::datatype() const 
{ 
	return m_Datatype; 
}
    
const std::string&
UniformBase::name() const 
{ 
	return m_Name; 
}

}
}
