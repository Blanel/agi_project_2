#ifndef IMAGE2D_H_
#define IMAGE2D_H_

#include "Types.h"
#include <vector>
#include <iostream>
#include <cassert>
#include <fstream>
#include <cstring>

#include "SDL_Image.h"

#include <iterator>

namespace revel
{

enum class PixelFormat
{
	RGB_U8,
	RGBA_U8,
	GRAY_U8,
	GRAY_F32,
	UNDEFINED
};

enum class ImageFormat
{
	TGA,
	UNDEFINED
};


namespace pixel
{

//forward decl
struct RGB_u8;
struct RGBA_u8;
struct Gray_u8;
struct Gray_f32;

struct RGB_u8
{
	RGB_u8();
	RGB_u8(u8 r, u8 g, u8 b);
	RGB_u8(const RGB_u8& c);
	RGB_u8(const RGBA_u8& c);
	RGB_u8(const Gray_u8& c);
	RGB_u8(const Gray_f32& c);

	static PixelFormat pixel_format();

	u8 r, g, b;
};

struct RGBA_u8
{
	RGBA_u8();
	RGBA_u8(u8 r, u8 g, u8 b, u8 a);
	RGBA_u8(const RGBA_u8& c);
	RGBA_u8(const RGB_u8& c, u8 a = 255);
	RGBA_u8(const Gray_f32& c);

	static PixelFormat pixel_format();

	u8 r, g, b, a;
};

struct Gray_u8
{
	Gray_u8(u8 val = 0);

	static PixelFormat pixel_format();

	u8 val;
};

struct Gray_f32
{
	Gray_f32(f32 val = 0);

	static PixelFormat pixel_format();

	f32 val;
};

} // ::revel::pixel



template <typename T>
class Image2D
{
	std::vector<T> m_Pixels;
	u32 m_Width, m_Height;
	PixelFormat m_PixelFormat;

public:	
	Image2D(u32 w, u32 h, T val = 0)
		: m_Pixels(w * h, val)
		, m_Width(w)
		, m_Height(h)
		, m_PixelFormat(T::pixel_format())
	{}

	template <typename U>
	Image2D(const Image2D<U>& img)
		: m_Pixels(img.width() * img.height())
		, m_Width(img.width())
		, m_Height(img.height())
		, m_PixelFormat(T::pixel_format())
	{
		for (u32 i = 0; i < m_Pixels.size(); ++i)
		{
			m_Pixels[i] = img.data()[i];
		}
	}

	Image2D(u32 w, u32 h, const std::vector<T>& pixeldata)
		: m_Pixels(pixeldata)
		, m_Width(w)
		, m_Height(h)
		, m_PixelFormat(T::pixel_format())	
	{
		assert(w * h == pixeldata.size());
	}

	Image2D(const std::string& filename)
	{
		SDL_Surface* image = IMG_Load(filename.c_str());
		SDL_PixelFormat* format = image->format;

		auto dataptr = static_cast<T*>(image->pixels);

/*
		if (image)
		{
			m_Width = image->w;
			m_Height = image->h;
			m_PixelFormat = T::pixel_format();

			u32 pixelcount = m_Width * m_Height;

			m_Pixels.reserve(pixelcount);

			//std::copy(&dataptr, &dataptr + pixelcount, std::back_inserter(m_Pixels));			

			SDL_FreeSurface(image);
		}
		else
		{
			throw std::exception();
		}
		*/
	}

/*
	template <typename... Args>
	Image2D(u32 w, u32 h, Args&&... args)
		: m_Pixels(w*h, std::forward<Args>(args)...)
		, m_Width(w)
		, m_Height(h)
		, m_PixelFormat(T::pixel_format())
	{}
*/
	virtual ~Image2D()
	{}

	u32 width() const 
	{ 
		return m_Width; 
	}

	u32 height() const 
	{ 
		return m_Height; 
	}

	PixelFormat pixel_format() const
	{
		return m_PixelFormat;
	}

	T& operator()(u32 x, u32 y) 
	{ 
		return m_Pixels[y*m_Width + x]; 
	}
	const T& operator()(u32 x, u32 y) const 
	{ 
		return m_Pixels[y*m_Width + x]; 
	}

	const std::vector<T>& data() const
	{
		return m_Pixels;
	}
};

} // ::revel

#endif // IMAGE2D_H_