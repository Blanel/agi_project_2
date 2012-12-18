#ifndef SURFACE_H_
#define SURFACE_H_

#include "Types.h"
#include <vector>

namespace revel
{

	
template <typename T>
class Surface
{
	std::vector<T> m_Data;
	u32 m_Width;
	u32 m_Height;



public:
	enum class Origin
	{
		LOWER_LEFT,
		UPPER_LEFT
	};

private:
	Origin m_Origin;

public:

	Surface(u32 w, u32 h)
		: m_Data(w*h)
		, m_Width(w)
		, m_Height(h)
		, m_Origin(Origin::LOWER_LEFT)
	{}

	virtual ~Surface()
	{}

	u32 width() const { return m_Width; }
	u32 height() const { return m_Height; }

	const T& operator()(u32 x, u32 y) const { return m_Data[y * m_Width + x]; }
	T& operator()(u32 x, u32 y) { return m_Data[y * m_Width + x]; }

	const std::vector<T>& data() const { return m_Data; }
	std::vector<T>& data() { return m_Data; }
};

}

#endif // SURFACE_H_