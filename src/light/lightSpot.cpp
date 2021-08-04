#include "lightSpot.h"

lightSpot::lightSpot(vec3 _position, vec3 _angle, vec3 _color):
	position(_position), angle(_angle), color(_color)
{
	UpdateDirectional();
}

lightSpot::~lightSpot()
{
	
}


void lightSpot::UpdateDirectional()
{
	direction = vec3(0.0f, 0.0f, 1.0f);
	direction = rotateZ(direction, angle.z);
	direction = rotateX(direction, angle.x);
	direction = rotateY(direction, angle.y);

	direction = -1.0f * direction;
}
