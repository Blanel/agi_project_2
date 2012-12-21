#version 410

//uniform sampler2D diffuseMap;

//in vec2 UV;

uniform vec3 r_Color = vec3(1.0);
out vec4 FragmentColor;

void main()
{
	FragmentColor = vec4(r_Color, 1.0);
	//vec3 diffuse_col = texture(diffuseMap, UV);
    //FragmentColor = vec4(0.8, 0.2, 0.2, 1.0);
}
