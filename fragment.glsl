#version 330 core

in vec3 fragmentNormal;
in vec3 vPos;

out vec4 color;

struct light
{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	vec3	position;
};

struct material
{
	vec3	ka;
	vec3	kd;
	vec3	ks;
	float	d;
	float	ns;
	int		illum;
};

#define MAX_LIGHTS 10

uniform	vec3 eyePos;
uniform	int numLights;
uniform	light lights[MAX_LIGHTS];
uniform	material materials;

// vec3	DirectIllumination(vec3 P, vec3 N, vec3 lightCentre, float lightRadius, vec3 lightColour, float cutoff)
// {
// 	// calculate normalized light vector and distance to sphere light surface
// 	float r = lightRadius;
// 	vec3 L = lightCentre - P;
// 	float distance = length(L);
// 	float d = max(distance - r, 0);
// 	L /= distance;

// 	// calculate basic attenuation
// 	float denom = d/r + 1;
// 	float attenuation = 1 / (denom * denom);

// 	// scale and bias attenuation such that:
// 	//	attenuation == 0 at extent of max influence
// 	//	attenuation == 1 when d == 0
// 	attenuation = (attenuation - cutoff) / (1 - cutoff);
// 	attenuation = max(attenuation, 0);

// 	float dot = max(dot(L, N), 0);
// 	return lightColour * dot * attenuation;
// }

void	main(void)
{
	vec3 N = normalize(fragmentNormal);
	vec3 finalColor = vec3(0.0, 0.0, 0.0);

	for (int i = 0; i < numLights; i++)
	{
		vec3 L = normalize( lights[i].position - vPos ); //pos
		vec3 E = normalize( -eyePos - vPos ); // we are in Eye Coordinates, so EyePos is (0,0,0)
		vec3 R = normalize( -reflect( L, N ) );

		//calculate Ambient Term:
		vec3 Iamb = normalize(lights[i].ambient * materials.ka); //ambiant

		//calculate Diffuse Term:
		float diffuseFactor = clamp(dot(N, -L), 0.0, 1.0);
		vec3 Idiff = normalize(lights[i].diffuse * materials.kd) * diffuseFactor; //difuse
		// Idiff = clamp( Idiff, 0.0, 1.0 );

		// calculate Specular Term:
		float specularFactor = dot(R, E);
		specularFactor = clamp(pow(specularFactor, 0.5 * materials.illum), 0.0, 1.0);
		vec3 Ispec  = vec3(0, 0, 0);
		if (specularFactor > 0)
		{
			Ispec = normalize(lights[i].specular * materials.ks) * 0.5 * materials.illum * specularFactor;
		}
		// vec3 Ispec = normalize(lights[i].specular * materials.ks) * pow( max( dot( R, E ), 0.0 ), 0.5 * materials.illum );//specular, shininess
		// Ispec = clamp( Ispec, 0.0, 1.0 );


		float r = 8.0;
		float cutoff = 0.00;
		L = lights[i].position - vPos;
		float distance = length(L);
		float d = max(distance - r, 0.0);
		L /= distance;

		// calculate basic attenuation
		float denom = d / r + 1;
		float attenuation = 1 / (denom * denom);

		// scale and bias attenuation such that:
		//	attenuation == 0 at extent of max influence
		//	attenuation == 1 when d == 0
		attenuation = ( attenuation - cutoff ) / ( 1 - cutoff );
		attenuation = max(attenuation, 0 );

		float dot = max( dot( L, N ), 0 );
		finalColor += (Iamb + Idiff + Ispec) * attenuation;
		//finalColor += DirectIllumination(vPos, N, lights[i].position, 8.0, Iamb + Idiff + Ispec, 0.1);
	}

	// write Total Color:
	color = vec4(finalColor, materials.d);
}
