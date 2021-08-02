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
	vec3 CarmeraVec = normalize(CameraPos - FragPos); // View lighting.
	float specularAmount = pow(max(dot(CarmeraVec, reflectVec), 0), material.shininess);

	vec3 ambientColor = material.ambient * ambientColor * texture(material.diffuse, TexCoords).rgb;
	vec3 specularVec = texture(material.specular, TexCoords).rgb * specularAmount * lightColor;
	vec3 diffuse =  dot(lightDir, Normal) * lightColor * texture(material.diffuse, TexCoords).rgb;

	FragColor = vec4((ambientColor  + diffuse + specularVec) * objColor, 1.0);
}