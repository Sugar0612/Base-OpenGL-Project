#pragma once
#include <glm.hpp>
#include <gtx/rotate_vector.hpp>

using namespace::glm;

class lightSpot
{
public:
	vec3 position;
	vec3 angle;
	vec3 color;
	vec3 direction;

	float cosPhyInner = 0.9f;
	float cosPhyOutter = 0.85f;


	lightSpot(vec3 _position, vec3 _angle, vec3 _color = vec3(1.0f, 1.0f, 1.0f));
	~lightSpot();

	void UpdateDirectional();
};