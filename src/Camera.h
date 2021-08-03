#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>

using namespace::glm;
using namespace::std;

class Camera
{
public:
	Camera(vec3 cameraPos, vec3 targetPos, vec3 worldUp);
	Camera(vec3 cameraPos, float pitch, float yaw, vec3 worldUp);
	~Camera() = default;

	vec3 camera_Pos;
	vec3 forWord;
	vec3 world_Up;
	vec3 right;
	vec3 up;

	float Yaw = 0.0f, Pitch = 0.0f;

	float speedX = 0.0f;
	float speedZ = 0.0f;
	float speedY = 0.0f;

	mat4 getViewMatrix();
	void setViewPos(float dir_x, float dir_y);
	void set_Camera_Pos();
private:
	void updataCameraPos();
};

