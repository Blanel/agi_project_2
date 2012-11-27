#ifndef UNIFORM_H
#define UNIFORM_H

#include <string>

namespace revel
{
namespace renderer
{

enum class UniformDatatype
{
    INT32,
    UINT32,
    FLOAT32,
    VEC2_F32,
    VEC3_F32,
    VEC4_F32,
    MAT2_F32,
    MAT2X3_F32,
    MAT2X4_F32,
    MAT3X2_F32,
    MAT3_F32,
    MAT3X4_F32,
    MAT4X2_F32,
    MAT4X3_F32,
    MAT4_F32,
    UNDEFINED
};

class UniformBase
{
    std::string m_Name;
    UniformDatatype m_Datatype;

public:
    UniformBase(const std::string& name, UniformDatatype type = UniformDatatype::UNDEFINED);
    virtual ~UniformBase();

    UniformDatatype datatype() const;
    const std::string& name() const;
};


template <typename T>
class Uniform : public UniformBase
{
protected:
    T m_Value;
  
public:
    Uniform(const std::string& name, UniformDatatype type = UniformDatatype::UNDEFINED)
        : UniformBase(name, type)
    {}

    virtual ~Uniform()
    {}

    virtual Uniform& operator=(const T& value) = 0;
    virtual void set_value(const T& value) = 0;
};


}
}

#endif // UNIFORM_H
