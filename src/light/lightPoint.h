#pragma once
#include <glm.hpp>
#include <gtx/rotate_vector.hpp>

using namespace::glm;

class lightPoint
{
public:
	vec3 position;
	vec3 direction;
	vec3 angle;
	vec3 color;

	lightPoint(vec3 _position, vec3 _angle, vec3 _color = vec3(1.0f, 1.0f, 1.0f));
	~lightPoint();
	
	float constant;
	float linear; // 一次
	float quadratic; // 二次

};

