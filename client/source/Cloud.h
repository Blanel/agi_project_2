#ifndef CLOUD_H_
#define CLOUD_H_

#include "renderer/VertexArray.h"
#include "renderer/RenderContext.h"
#include "BoundingVolume.h"

namespace revel
{
	
class Cloud
{
	renderer::VertexArray m_VA;
	BBox m_BoundingBox;
	//TextureCube m_FractalCube;

	ShaderProgram m_pShaderProgram;


	void draw(const std::shared_ptr<renderer::RenderContext>& ctx)
	{
		//create framebuffer and render to texture target
		//load

	}


	
};

}

#endif // CLOUD_H_