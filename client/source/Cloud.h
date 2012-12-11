#ifndef CLOUD_H_
#define CLOUD_H_

#include "renderer/VertexArray.h"
#include "renderer/RenderContext.h"
#include "BoundingVolume.h"
#include "Image2D.h"
#include "Camera.h"

#include "SimplexNoise.h"

namespace revel
{


class CubeImage
{
	std::shared_ptr<Image2D<pixel::RGBA_u8>> m_pTop;
	std::shared_ptr<Image2D<pixel::RGBA_u8>> m_pBottom;
	std::shared_ptr<Image2D<pixel::RGBA_u8>> m_pLeft;
	std::shared_ptr<Image2D<pixel::RGBA_u8>> m_pRight;
	std::shared_ptr<Image2D<pixel::RGBA_u8>> m_pFront;
	std::shared_ptr<Image2D<pixel::RGBA_u8>> m_pBack;

public:
	CubeImage(u32 w, u32 h)
	{
		
		m_pTop 		= std::make_shared<Image2D<pixel::RGBA_u8>>(w, h);
		m_pBottom 	= std::make_shared<Image2D<pixel::RGBA_u8>>(w, h);
		m_pLeft 	= std::make_shared<Image2D<pixel::RGBA_u8>>(w, h);
		m_pRight 	= std::make_shared<Image2D<pixel::RGBA_u8>>(w, h);
		m_pFront 	= std::make_shared<Image2D<pixel::RGBA_u8>>(w, h);
		m_pBack 	= std::make_shared<Image2D<pixel::RGBA_u8>>(w, h);
	}

	const std::shared_ptr<Image2D<pixel::RGBA_u8>>& top() { return m_pTop; }
	const std::shared_ptr<Image2D<pixel::RGBA_u8>>& bottom() { return m_pBottom; }
	const std::shared_ptr<Image2D<pixel::RGBA_u8>>& left() { return m_pLeft; }
	const std::shared_ptr<Image2D<pixel::RGBA_u8>>& right() { return m_pRight; }
	const std::shared_ptr<Image2D<pixel::RGBA_u8>>& front() { return m_pFront; }
	const std::shared_ptr<Image2D<pixel::RGBA_u8>>& back() { return m_pBack; }

	static CubeImage generate_fractal_cube()
	{
		CubeImage cube(256, 256);
		SimplexNoise simplex;

		simplex.set_amplitude(1.0f);
		simplex.set_frequency(1.0f);
		simplex.set_octaves(1);
		simplex.set_persistance(1.0f);

		for (u32 y = 0; y < 256; ++y)
		{
			for (u32 x = 0; x < 256; ++x)
			{
				auto n = simplex.noise(x, y);
				f32 nn = (n + 1.0f) * 128.0f - 1;
				cube.front()->operator()(x,y) = pixel::RGBA_u8(nn, nn, nn, 255);
			}			
		}

		return cube;
	}

};


class Cloud
{
	// renderer::VertexArray m_VA;
	BBox m_BoundingBox;
	//TextureCube m_FractalCube;

	std::shared_ptr<ShaderProgram> m_pShaderProgram;

public:
	void draw(const std::shared_ptr<renderer::RenderContext>& ctx)
	{
		//create framebuffer and render to texture target
		//load

	}
};

class CloudLayer
{

	void draw(const std::shared_ptr<renderer::RenderContext>& ctx, const std::shared_ptr<Camera>& cam)
	{
		
	}
};

}

#endif // CLOUD_H_