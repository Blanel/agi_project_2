#version 410

uniform mat4 r_MVP = mat4(1.0);

layout(location = 0) in vec3 in_VtxPosition;
//layout(location = 1) in vec2 in_TexCoord0;

//out vec2 UV;

void main()
{
	//UV = in_TexCoord0;
    gl_Position = r_MVP * vec4(in_VtxPosition, 1.0);
}
