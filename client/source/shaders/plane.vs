#version 410

uniform mat4 r_MVP = mat4(1.0);

in vec3 in_VtxPosition;
in vec2 in_TexCoord0;

out vec2 TexCoord0;

void main()
{
	TexCoord0 = in_TexCoord0;
    gl_Position = r_MVP * vec4(in_VtxPosition, 1.0);
}
