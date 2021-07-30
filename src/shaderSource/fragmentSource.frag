#version 330 core			
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 CameraPos;

out vec4 FragColor;
void main() {
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 reflectVec = reflect(-lightDir, Normal);
	vec3 CarmeraVec = max(normalize(CameraPos - FragPos), 0);

	vec3 specularVec = vec3(pow(max(dot(CarmeraVec, reflectVec), 0), 256)) * lightColor;
	vec3 diffuse = dot(lightDir, Normal) * lightColor;
	FragColor = vec4((ambientColor  + diffuse + specularVec) * objColor, 1.0);
}