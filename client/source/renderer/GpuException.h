#ifndef GPUEXCEPTION_H
#define GPUEXCEPTION_H

#include <stdexcept>

namespace revel
{
namespace renderer
{

class GpuException : public std::runtime_error
{
public:
    GpuException(const std::string& str)
        : std::runtime_error(str)
    {}

};

} // ::revel::renderer
} // ::revel

#endif // GPUEXCEPTION_H
