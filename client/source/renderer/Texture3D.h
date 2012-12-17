#ifndef TEXTURE3D_H_
#define TEXTURE3D_H_

#include "GpuObject.h"

namespace revel
{
namespace renderer
{
		

class Texture3D : public GpuObject
{
public:
	Texture3D() {}
	virtual ~Texture3D() {}


	virtual void bind() = 0;
	virtual void unbind() = 0;

	
};

} // ::revel::renderer
} // ::revel

#endif // TEXTURE3D_H_