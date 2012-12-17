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
	u32 m_Width;
	u32 m_Height;
	u32 m_Depth;

public:
	Image3D(u32 w, u32 h, u32 d)	
		: m_Layers(d, Image2D<T>(w, h))
		, m_Width(w)
		, m_Height(h)
		, m_Depth(d)
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

	const Image2D<T>& layer(u32 l) const
	{
		return m_Layers[l];
	}

	Image2D<T>& layer(u32 l)
	{
		return m_Layers[l];
	}

	u32 width() const
	{
		return m_Width;
	}

	u32 height() const
	{
		return m_Height;
	}

	u32 depth() const
	{
		return m_Depth;
	}
	
};

}

#endif // IMAGE3D_H_