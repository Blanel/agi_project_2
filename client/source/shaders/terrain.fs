#version 410

uniform sampler2D diffuseMap;

layout (location = 0) out vec4 FragmentColor;

in vec3 Normal;
in vec2 UV;

void main()
{	
	FragmentColor = vec4(Normal, 1.0) + texture(diffuseMap, UV) * 0.001;
}
