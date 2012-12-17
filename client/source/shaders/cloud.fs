#version 410

#define N = 128;

void ray_march(vec3 in, vec3 view, float distance, vec3 extinction, vec3 inScattering)
{
	vec3 step = view * distance / (N + 1);
	float stepSize = length(step);
	vec3 currentpos = in + (N + 0.5) * step;

	extinction = 1.0;
	inScattering = 0.0;

	for (int stepIndex = 0; stepIndex < N; stepIndex++)
	{
		vec2 sigma_t = get_extinction_coeff(currentpos);
		vec2 sigma_s = get_scattering_coeff(currentpos);

		vec3 currentStepExtinction = exp(-sigma_t * stepSize);

		extinction *= currentStepExtinction;
		inScattering += currentStepExtinction * sigma_s * stepSize * compute_radiance(currentpos, view);

		currentpos -= step;
	}
}


void main()
{
	
}