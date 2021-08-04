#pragma once
#include <glm.hpp>
#include <gtx/rotate_vector.hpp>

using namespace::glm;

class LightDirectional
{
public:
	vec3 position;
	vec3 angle;
	vec3 direction = vec3(0, 0, 0.1f);
	vec3 color;

	LightDirectional(vec3 _position, vec3 _angle, vec3 _color = vec3(1.0f, 1.0f, 1.0f));
	~LightDirectional();

	void UpdateDirectional();
};

