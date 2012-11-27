#ifndef IMAGE3D_H_
#define IMAGE3D_H_

#include <vector>
#include "Image2D.h"

namespace revel
{

template <typename T>	
class Image3D
{
	std::vector<Image2D<T>> m_Layers;

public:
	Image3D(u32 w, u32 h, u32 d)	
		: m_Layers(d, Image2D<T>(w, h))
	{}

	~Image3D()
	{}

	const T& operator()(u32 x, u32 y, u32 z) const
	{
		return m_Layers[z](x, y);
	}

	T& operator()(u32 x, u32 y, u32 z)
	{
		return m_Layers[z](x, y);
	}
	
};

}

#endif // IMAGE3D_H_