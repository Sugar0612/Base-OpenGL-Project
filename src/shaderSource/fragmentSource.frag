#version 330 core			
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct lightDir {
	vec3 pos;
	vec3 dir;
	vec3 color;
};

struct lightPtr {
	vec3 pos;
	vec3 dir;
	vec3 color;

	float constant;
	float linear;
	float qeadratic;
};

struct lightSpt {
	vec3 pos;
	vec3 dir;
	vec3 color;

	float constant;
	float linear;
	float qeadratic;

	float cosPhyInner;
	float cosPhyOutter;
};

uniform Material material;
uniform lightDir lightD;
uniform lightPtr lightPt[4];
uniform lightSpt lightSp;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDirUniform;
uniform vec3 CameraPos;

out vec4 FragColor;

vec3 calcLightDirectional(lightDir light, vec3 normal, vec3 cdir) {
	vec3 result;

	//diffues
	vec3 diffuse = max(dot(light.dir, normal), 0) * light.color;

	//specular
	vec3 reflectVec = reflect(-normalize(light.pos - FragPos), normal);
	float specularAmount = pow(max(dot(reflectVec, cdir), 0), material.shininess) ;

	vec3 specular = specularAmount * light.color * texture(material.specular, TexCoords).rgb;
	
	result = diffuse + specularAmount;

	return result;
}

vec3 calcLightPoint(lightPtr light, vec3 normal, vec3 cdir) {
	vec3 res;

	//attenuation
	float dist = length(light.pos - FragPos);
	float attenuation = 1 / (light.constant + light.linear * dist + light.qeadratic * (dist * dist));

	//diffuse
	float diffIntensity = max(dot(normalize(light.pos - FragPos), normal), 0) * attenuation;
	vec3 diffuse = diffIntensity * light.color * texture(material.diffuse, TexCoords).rgb;
	
	//specular
	vec3 reflectVec = normalize(reflect(-normalize(light.pos - FragPos), normal));
	float specularAmount = pow(max( dot( reflectVec, cdir), 0), material.shininess);
	vec3 specular = specularAmount * light.color * texture(material.specular, TexCoords).rgb;
	res = diffuse + specular;
	return res;
}

vec3 calcLightSpot(lightSpt light, vec3 normal, vec3 cdir) {
	vec3 res;

	//attenuation
	float dist = length(light.pos - FragPos);
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.qeadratic * (dist * dist));
	float spotratio = 0.0f;
	float cosTheta = dot(normalize(FragPos - light.pos), -light.dir);

	if(cosTheta > light.cosPhyInner) spotratio = 1.0f;
	else if(cosTheta > light.cosPhyOutter) spotratio = (cosTheta - light.cosPhyOutter) / (light.cosPhyInner - light.cosPhyOutter);

	//diffuse 
	float diffIntensity = max( dot( normalize(light.pos - FragPos), normal), 0) * attenuation * spotratio;
	vec3 diffuse = diffIntensity * light.color * texture(material.diffuse, TexCoords).rgb;

	//specular
	vec3 reflectVec = normalize( reflect(-normalize(light.pos - FragPos), normal));
	float specularIntensity = pow( max( dot(reflectVec, cdir), 0), material.shininess) * attenuation * spotratio;
	vec3 specular = specularIntensity * light.color * texture(material.specular, TexCoords).rgb;

	res = diffuse + specular;
	return res;
}

void main() {
	vec3 aNormal = normalize(Normal);
	vec3 cameraDir = normalize(CameraPos - FragPos);
	vec3 ambientColor = material.ambient * texture(material.diffuse, TexCoords).rgb;

	vec3 synthLight = ambientColor;
	//synthLight += calcLightDirectional(lightD, aNormal, cameraDir);

	//for(int i = 0; i < 4; ++i) synthLight += calcLightPoint(lightPt[i], aNormal, cameraDir);

	synthLight += calcLightSpot(lightSp, aNormal, cameraDir);
	FragColor = vec4(synthLight, 1.0f);
}