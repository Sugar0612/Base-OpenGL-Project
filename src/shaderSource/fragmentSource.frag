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

struct lightPtr {
	float constant;
	float linear;
	float qeadratic;
};

struct lightSpt {
	float cosPhyInner;
	float cosPhyOutter;
};

uniform Material material;
uniform lightPtr lightPt;
uniform lightSpt lightSp;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDirUniform;
uniform vec3 CameraPos;

out vec4 FragColor;
void main() {
	//float dist = length(lightPos - FragPos);
	//float attenuation = 1.0f / (lightPt.constant + lightPt.linear * dist + lightPt.qeadratic * (dist * dist));
	

	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 reflectVec = reflect(-lightDir, Normal);  // Diffuse reflection.
	vec3 CarmeraVec = normalize(CameraPos - FragPos); // View lighting.
	float specularAmount = pow(max(dot(CarmeraVec, reflectVec), 0), material.shininess);

	vec3 ambientColor = material.ambient * ambientColor * texture(material.diffuse, TexCoords).rgb;
	vec3 specularVec = texture(material.specular, TexCoords).rgb * specularAmount * lightColor;
	vec3 diffuse =  dot(lightDir, Normal) * lightColor * texture(material.diffuse, TexCoords).rgb;

	float cosTheta = dot(normalize(FragPos - lightPos), -1 * lightDirUniform);

	float transition = 0.0f;
	if(cosTheta > lightSp.cosPhyInner) {
		transition = 1.0f;
	} else if(cosTheta > lightSp.cosPhyOutter) {
		transition = 1.0f - (cosTheta - lightSp.cosPhyInner) / (lightSp.cosPhyOutter - lightSp.cosPhyInner);	
	}

	FragColor = vec4((ambientColor  + (diffuse + specularVec) * transition) * objColor,  1.0);
}