#include "Texture2D.h"

namespace revel
{
namespace renderer
{

Texture2D::Texture2D(u32 w, u32 h, TextureFormat format, bool mimap)
	: m_Width(w)
	, m_Height(h)
	, m_InternalFormat(format)
	, m_MipMapped(true)
{
}

} // ::revel::renderer
} // ::revel
