#ifndef IMAGE2D_H_
#define IMAGE2D_H_

#include "Types.h"
#include <vector>
#include <iostream>
#include <cassert>
#include <fstream>
#include <cstring>

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

struct RGB_u8
{
	RGB_u8(u8 r, u8 g, u8 b) : r(r), g(g), b(b) {}

	static PixelFormat pixel_format() { return PixelFormat::RGB_U8; }

	u8 r, g, b;
};

struct RGBA_u8
{
	RGBA_u8(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) {}

	static PixelFormat pixel_format() { return PixelFormat::RGBA_U8; }

	u8 r, g, b, a;
};

struct Gray_u8
{
	Gray_u8(u8 val) : val(val) {}

	static PixelFormat pixel_format() { return PixelFormat::GRAY_U8; }

	u8 val;
};

struct Gray_f32
{
	Gray_f32(f32 val) : val(val) {}

	static PixelFormat pixel_format() { return PixelFormat::GRAY_F32; }

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


	Image2D(u32 w, u32 h, const std::vector<T>& pixeldata)
		: m_Pixels(pixeldata)
		, m_Width(w)
		, m_Height(h)
		, m_PixelFormat(T::pixel_format())	
	{
		assert(w * h == pixeldata.size());
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

class TGAException : public std::exception
{

    std::string m_Msg;
public:
    TGAException(const std::string& str)
        : m_Msg(str)
    {}
};

enum class TGAEnc
{
    RawIndexed = 1,
    RawRGB = 2,
    RunLengthEncIndexed = 9,
    RunLengthEncRGB = 10
};
#ifdef _MSC_VER
#pragma pack(push)
struct TGAHeader
{
    i8  IDLength;
    i8  ColorMapType;
    i8  DataTypeCode;

    i16 ColorMapOrigin;
    i16 ColorMapLength;
    i8  ColorMapDepth;

    i16 XOrigin;
    i16 YOrigin;
    i16 Width;
    i16 Height;
    i8  BPP;
    i8  Descriptor;
};
#pragma pack(pop)
#else
struct TGAHeader
{
    i8  IDLength;
    i8  ColorMapType;
    i8  DataTypeCode;

    i16 ColorMapOrigin;
    i16 ColorMapLength;
    i8  ColorMapDepth;

    i16 XOrigin;
    i16 YOrigin;
    i16 Width;
    i16 Height;
    i8  BPP;
    i8  Descriptor;
} __attribute__ ((__packed__));
#endif

class TGA
{
	static void write(const std::string& filename, const TGAHeader& header, const i8* dataptr, u32 byte)
	{
        if (dataptr == nullptr)
            throw TGAException("Invalid data source pointer");
        
        std::ofstream imagefile(filename.c_str(), std::ios::out | std::ios::binary);

        imagefile.write(reinterpret_cast<const i8*>(&header), sizeof(TGAHeader));
        imagefile.write(dataptr, byte);
        imagefile.close();
	}

public:	
	template <typename T>
	static void write(const std::string& filename, const Image2D<T>& img)
	{
        TGAHeader header;
        memset(&header, 0, sizeof(TGAHeader));

        header.Width = img.width();
        header.Height = img.height();
        header.BPP = sizeof(T) * 8;

        std::cout << sizeof(header) << std::endl;

        bool flip_rb = false;

        switch(img.pixel_format())
        {
    	case PixelFormat::RGB_U8:
    		header.DataTypeCode = 0x2;
    		header.Descriptor = 0x20;
    		flip_rb = true;
    		break;
    	case PixelFormat::RGBA_U8:
    		header.DataTypeCode = 0x2;
    		header.Descriptor = 0x28;
    		flip_rb = true;
    		break;
		case PixelFormat::GRAY_U8:
			header.DataTypeCode = 0x3;
			header.Descriptor |= (1 << 5);
			break;
        }

		auto dataptr = reinterpret_cast<const i8*>(&(img.data()[0]));
		std::vector<T> pixeldata;

        if (flip_rb)
        {
	        pixeldata = img.data();

	        for (auto& pixel : pixeldata)
	        {
	        	std::swap(pixel.r, pixel.b);
	        }

	        dataptr = reinterpret_cast<const i8*>(&(pixeldata.data()[0]));
        }

        u32 byte = img.width() * img.height() * sizeof(T);

        write(filename.c_str(), header, dataptr, byte);
	}
};


} // ::revel

#endif // IMAGE2D_H_