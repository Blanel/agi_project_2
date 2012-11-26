#ifndef TGA_H_
#define TGA_H_

#include "Image2D.h"

namespace revel
{

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
#pragma pack(push,1)
struct TGAHeader
{
    i8 IDLength;
    i8 ColorMapType;
    i8 DataTypeCode;

    i16 ColorMapOrigin;
    i16 ColorMapLength;
    i8 ColorMapDepth;

    i16 XOrigin;
    i16 YOrigin;
    i16 Width;
    i16 Height;
    i8 BPP;
    i8 Descriptor;
};
#pragma pack(pop)
#else
struct TGAHeader
{
    i8 IDLength;
    i8 ColorMapType;
    i8 DataTypeCode;

    i16 ColorMapOrigin;
    i16 ColorMapLength;
    i8 ColorMapDepth;

    i16 XOrigin;
    i16 YOrigin;
    i16 Width;
    i16 Height;
    i8 BPP;
    i8 Descriptor;
} __attribute__ ((__packed__));
#endif


class TGA
{
	static void write(const std::string& filename, const TGAHeader& header, const i8* dataptr, u32 byte);

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

}

#endif // TGA_H_