#version 410

in vec3 Normal;
in vec2 TexCoord;

uniform vec3 sunDirection = vec3(1, 0, 1);

out vec4 FragmentColor;

void main()
{
	vec3 n = normalize(Normal);
	float nDotL = max(0.0, dot(n, normalize(sunDirection)));

	vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);
	vec4 diffuse = vec4(0.7, 0.8, 0.7, 1.0) * nDotL;

	FragmentColor = ambient + diffuse;
	// FragmentColor = vec4(1, 1, 1, 1.0);
}
