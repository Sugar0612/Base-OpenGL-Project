#version 330 core
layout (location = 3) in vec3 aPos;
layout (location = 4) in vec3 aNormal;
layout (location = 5) in vec2 aTexCoords;

//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main() {
    gl_Position = projMat * viewMat * modelMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	FragPos = (modelMat * vec4(aPos.xyz, 1.0f)).xyz;
	Normal = mat3(transpose(inverse(modelMat))) * aNormal;
	TexCoords = aTexCoords;
};