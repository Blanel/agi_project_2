

uniform mat4 r_MVP;

in vec3 in_vertexPos;
in vec2 in_vertexUV0;

out vec2 uv0;

void main()
{
	gl_Position = r_MVP * in_vertexPos;
	uv0 = in_vertexUV0;n
}