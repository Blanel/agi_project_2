#version 410

uniform sampler2D fbo_texture;
in vec2 uv0;
out vec4 color;

void main()
{
	vec2 texcoord = uv0;

	//texcoord.x += sin(texcoord.y *4*2*3.141592 + 3.0) / 100;

	color = texture2D(fbo_texture, texcoord);
}