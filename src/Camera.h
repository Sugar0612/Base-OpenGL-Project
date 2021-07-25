#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

using namespace::glm;

class Camera
{
public:
	Camera(vec3 cameraPos, vec3 targetPos, vec3 worldUp);
	~Camera() = default;

	vec3 camera_Pos, forWord, world_Up, right, up;

	mat4 getViewMatrix();

};

