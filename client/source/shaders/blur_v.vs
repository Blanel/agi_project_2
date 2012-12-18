#version 410

in vec3 in_vertexPos;
out vec2 uv0;

void main()
{
	gl_Position = vec4(in_vertexPos, 1.0);
	uv0 = ((in_vertexPos + 1.0) / 2.0).xy;
}