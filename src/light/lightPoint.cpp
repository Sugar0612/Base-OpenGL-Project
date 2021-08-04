#include "lightPoint.h"

lightPoint::lightPoint(vec3 _position, vec3 _angle, vec3 _color): 
	position(_position), angle(_angle), color(_color)
{
	this->constant = 1.0f;
	this->linear = 0.09f;
	this->quadratic = 0.032f;
}

lightPoint::~lightPoint()
{
}
