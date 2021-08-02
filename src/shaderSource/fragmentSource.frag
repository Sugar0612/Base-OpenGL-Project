#version 330 core			
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
	vec3 ambient;
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 CameraPos;

out vec4 FragColor;
void main() {
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 reflectVec = reflect(-lightDir, Normal);  // Diffuse reflection.
	vec3 CarmeraVec = max(normalize(CameraPos - FragPos), 0); // View lighting.

	vec3 ambientColor = material.ambient * ambientColor;
	vec3 specularVec = material.specular *  vec3(pow(max(dot(CarmeraVec, reflectVec), 0), material.shininess)) * lightColor;
	vec3 diffuse =  dot(lightDir, Normal) * lightColor * texture(material.diffuse, TexCoords).rgb;
	FragColor = vec4((ambientColor  + diffuse + specularVec) * objColor, 1.0);
}