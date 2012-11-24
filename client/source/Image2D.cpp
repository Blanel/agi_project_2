#include "Image2D.h"

namespace revel
{
namespace pixel
{
	
RGB_u8::RGB_u8() : r(0), g(0), b(0) {}
RGB_u8::RGB_u8(u8 r, u8 g, u8 b) : r(r), g(g), b(b) {}
RGB_u8::RGB_u8(const RGB_u8& c) : r(c.r), g(c.g), b(c.b) {}
RGB_u8::RGB_u8(const RGBA_u8& c) : r(c.r), g(c.g), b(c.b) {}
RGB_u8::RGB_u8(const Gray_u8& c) : r(c.val), g(c.val), b(c.val) {}
RGB_u8::RGB_u8(const Gray_f32& c) : r(c.val / 255), g(c.val / 255), b(c.val / 255) {}

PixelFormat RGB_u8::pixel_format() { return PixelFormat::RGB_U8; }

RGBA_u8::RGBA_u8() : r(0), g(0), b(0), a(255) {}
RGBA_u8::RGBA_u8(u8 r, u8 g, u8 b, u8 a) : r(r), g(g), b(b), a(a) {}
RGBA_u8::RGBA_u8(const RGBA_u8& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
RGBA_u8::RGBA_u8(const RGB_u8& c, u8 a) : r(c.r), g(c.g), b(c.b), a(a) {}

PixelFormat RGBA_u8::pixel_format() { return PixelFormat::RGBA_U8; }

Gray_u8::Gray_u8(u8 val) : val(val) {}

PixelFormat Gray_u8::pixel_format() { return PixelFormat::GRAY_U8; }

Gray_f32::Gray_f32(f32 val) : val(val) {}

PixelFormat Gray_f32::pixel_format() { return PixelFormat::GRAY_F32; }

} // ::revel::pixel
} // ::revel
