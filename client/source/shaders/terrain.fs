#version 410

uniform sampler2D diffuseMap;

layout (location = 0) out vec4 FragmentColor;

in vec3 Normal;
in vec2 UV;

void main()
{	
	// FragmentColor = vec4(Normal, 1.0) + texture(diffuseMap, UV) * 0.001;

	vec3 n = normalize(Normal);
	float nDotL = max(0.0, dot(n, normalize(vec3(1, 0, 1))));

	vec4 ambient = vec4(0.06, 0.03, 0.02, 1.0);
	vec4 diffuse = vec4(0.4, 0.2, 0.15, 1.0) * nDotL;

	FragmentColor = ambient + diffuse;
}
