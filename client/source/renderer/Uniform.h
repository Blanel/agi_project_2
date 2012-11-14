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
    MAT4_F32
};


class Uniform
{
public:

protected:
    std::string m_Name;
    UniformDatatype m_Datatype;

    Uniform(const std::string& name, UniformDatatype type);

public:
    virtual ~Uniform();

    UniformDatatype datatype() const
    {
        return m_Datatype;
    }

    const std::string& name() const
    {
        return m_Name;
    }

};


template <typename T>
class UniformT
    : public Uniform
{
protected:    
    T m_Value;

public:
    UniformT(const std::string& name, UniformDatatype type)
        : Uniform(name, type)
    {

    }

    virtual ~UniformT()
    {

    }

public:
    virtual UniformT& operator=(const T& value) = 0;
};

}
}

#endif // UNIFORM_H
