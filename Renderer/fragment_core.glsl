#version 440

#define NR_LIGHTS 2

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;

	sampler2D diffuseTex;
	sampler2D specularTex;
};

struct Light
{
	vec4 lightVector;
	vec3 position;
	vec3 direction;
	float cutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

//############################################################# FUNCTION HEAD
vec3 calculateAmbient(Light light, Material material);
vec3 calculateDiffuse(Light light, Material material, vec3 vs_position, vec3 vs_normal);
vec3 calculateSpecular(Light light, Material material, vec3 vs_position, vec3 vs_normal, vec3 cameraPos);

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

//############################################################# UNIFORMS
uniform Material material;
uniform Light lightsArray[NR_LIGHTS];

uniform vec3 cameraPos;

//############################################################# FUNCTIONS

void main()
{
	vec3 ambientFinal = vec3(0.0f);
	vec3 diffuseFinal = vec3(0.0f);
	vec3 specularFinal = vec3(0.0f);

	for(int i = 0; i < NR_LIGHTS; i++)
	{
		Light light = lightsArray[i];
		vec3 newAmbientFinal = calculateAmbient(light, material);
		vec3 newDiffuseFinal = calculateDiffuse(light, material, vs_position, vs_normal);
		vec3 newSpecularFinal = calculateSpecular(light, material, vs_position, vs_normal, cameraPos);

		// POSITION LIGHTING - ATTENUATION
		if(light.lightVector.w == 1.0f)
		{
			float distance = length(light.position - vs_position);
			float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
			newAmbientFinal *= attenuation;
			newDiffuseFinal *= attenuation;
			newSpecularFinal *= attenuation;
		}
		ambientFinal += newAmbientFinal;
		diffuseFinal += newDiffuseFinal;
		specularFinal += newSpecularFinal;
	}

	//Final light
	fs_color = texture(material.diffuseTex, vs_texcoord) * (vec4(ambientFinal, 1.0f) + vec4(diffuseFinal, 1.0f) + vec4(specularFinal, 1.0f));
}


vec3 calculateAmbient(Light light, Material material)
{
	return light.ambient * material.ambient;
}

vec3 calculateDiffuse(Light light, Material material, vec3 vs_position, vec3 vs_normal)
{
	vec3 lightDir;
	
	// DIRECTION LIGHTING
	if(light.lightVector.w == 0.0f)
	{
		lightDir = normalize(-vec3(light.lightVector));
	}
	// POSITION LIGHTING
	else if(light.lightVector.w == 1.0f)
	{
		lightDir = normalize(vec3(light.lightVector) - vs_position);
	}

	float diffuse = clamp(dot(lightDir, vs_normal), 0, 1);
	vec3 diffuseFinal = light.diffuse * material.diffuse * diffuse;
	
	return diffuseFinal;
}

vec3 calculateSpecular(Light light, Material material, vec3 vs_position, vec3 vs_normal, vec3 cameraPos)
{
	vec3 lightDir;

	// DIRECTION LIGHTING
	if(light.lightVector.w == 0.0f)
	{
		lightDir = normalize(-vec3(light.lightVector));
	}
	// POSITION LIGHTING
	else if(light.lightVector.w == 1.0f)
	{
		lightDir = normalize(vec3(light.lightVector) - vs_position);
	}
	vec3 reflectDirVec = normalize(reflect(lightDir, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(vs_position - cameraPos);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), material.shininess);
	vec3 specularFinal = light.specular * material.specular * specularConstant * texture(material.specularTex, vs_texcoord).rgb;

	return specularFinal;
}

