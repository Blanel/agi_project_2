#version 410

uniform sampler2D diffuseMap;

layout (location = 0) out vec3 FragmentColor;

//in vec3 Position;
//in vec3 Normal;
in vec2 UV;

void main()
{	
	FragmentColor = vec4(1.0, 1.0, 1.0, 1.0) * texture(diffuseMap, UV);
}
