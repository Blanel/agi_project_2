in vec2 uv0;

uniform sampler2D scene_texture;
uniform float rt_w;
uniform float rt_h;

float offset[3] = float[](0.0, 1.3846153846, 3.2307692308);
float weight[3] = float[](0.2270270270, 0.3162162162, 0.0702702703);

out vec4 color;

void main()
{
	vec3 tc = vec3(1.0, 0.0, 0.0);

	vec2 uv = uv0;
	tc = texture2D(scene_texture, uv).rgb * weight[0];

	for (int i = 1; i < 3; ++i)
	{
		tv += texture2D(scene_texture, uv + vec2(0.0, offset[i])/rt_h).rgb * weight[i];
		tv += texture2D(scene_texture, uv - vec2(0.0, offset[i])/rt_h).rgb * weight[i];
	}

	color = vec4(tc, 1.0);
}