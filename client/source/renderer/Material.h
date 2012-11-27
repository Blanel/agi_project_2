#include <memory>

namespace revel
{
namespace renderer
{

class ShaderProgram;		

class RenderPass
{
	std::shared_ptr<ShaderProgram> m_pProgram;
	
public:
	RenderPass(const std::shared_ptr<ShaderProgram>& sp)
		: m_pProgram(sp)
	{}

	const std::shared_ptr<ShaderProgram>& shader_program() const
	{
		return m_pProgram;
	}
	

};

class Material
{

	

public:
	Material();
	virtual ~Material();

	
};


} // ::revel::renderer
} // ::revel
