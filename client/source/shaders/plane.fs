#version 410

uniform sampler2D diffuseMap;

in vec2 TexCoord0;
out vec4 FragmentColor;

void main()
{
	vec4 diffuseTx = texture2D(diffuseMap, TexCoord0);
	FragmentColor = diffuseTx;
    //FragmentColor = vec4(0.8, 0.2, 0.2, 1.0);
}
