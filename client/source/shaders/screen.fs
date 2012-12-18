#version 410

uniform sampler2D fbo_texture;
in vec2 uv0;
out vec4 color;

void main()
{
	color = texture2D(fbo_texture, uv0);
}