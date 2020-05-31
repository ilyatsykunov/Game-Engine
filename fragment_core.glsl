#version 440

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

struct Light
{
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
vec3 calculateAmbient(Material material);
vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0);
vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0, vec3 cameraPos);

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

//############################################################# UNIFORMS
uniform Material material;
uniform Light light;
uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 lightPos0;
uniform vec3 cameraPos;

//############################################################# FUNCTIONS

void main()
{

	vec3 ambientFinal = calculateAmbient(material);
	vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, lightPos0);
	vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, lightPos0, cameraPos);

	//Attenuation

	float distance = length(light.position - vs_position);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	ambientFinal *= attenuation;
	diffuseFinal *= attenuation;
	specularFinal *= attenuation;

	//Final light

	fs_color = texture(material.diffuseTex, vs_texcoord) * (vec4(ambientFinal, 1.0f) + vec4(diffuseFinal, 1.0f) + vec4(specularFinal, 1.0f));

}


vec3 calculateAmbient(Material material)
{
	return light.ambient * material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0)
{
	vec3 lightDir = normalize(-light.direction);


	float diffuse = clamp(dot(lightDir, vs_normal), 0, 1);
	vec3 diffuseFinal = light.diffuse * material.diffuse * diffuse;

	return diffuseFinal;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0, vec3 cameraPos)
{
	vec3 lightDir = normalize(-light.direction);
	vec3 reflectDirVec = normalize(reflect(lightDir, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(cameraPos - vs_position);
	float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 35);
	vec3 specularFinal = light.specular * material.specular * specularConstant * texture(material.specularTex, vs_texcoord).rgb;

	return specularFinal;
}

