#version 330 core			
in vec4 vertexColor;
in vec2 TexPos;

uniform sampler2D aTex;
uniform sampler2D aface;
uniform vec3 objColor;
uniform vec3 ambientColor;

out vec4 FragColor;
void main() {				
	FragColor = vec4(objColor * ambientColor, 1.0) * mix(texture(aTex, TexPos), texture(aface, TexPos), 0.3f);
}