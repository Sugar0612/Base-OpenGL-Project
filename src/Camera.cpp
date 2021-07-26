#include "Camera.h"

Camera::Camera (vec3 cameraPos, vec3 targetPos, vec3 worldUp): camera_Pos(cameraPos), world_Up(worldUp) {
	forWord = normalize(targetPos - cameraPos);
	right = normalize(cross(forWord, worldUp));
	up = normalize(cross(forWord, right));
}


Camera::Camera(vec3 cameraPos, float pitch, float yaw, vec3 worldUp): camera_Pos(cameraPos), world_Up(worldUp), Yaw(yaw), Pitch(pitch) {
	Pitch = radians(Pitch);
	Yaw = radians(Yaw);

	forWord.x = cos(Pitch) * sin(Yaw);
	forWord.y = sin(Pitch);
	forWord.z = cos(Pitch) * cos(Yaw);

	right = normalize(cross(forWord, world_Up));
	up = normalize(cross(forWord, right));
}

mat4 Camera::getViewMatrix() {
	return lookAt(camera_Pos, forWord + camera_Pos, world_Up);
}

void Camera::updataCameraPos() {

	forWord.x = cos(Pitch) * sin(Yaw);
	forWord.y = sin(Pitch);
	forWord.z = cos(Pitch) * cos(Yaw);

	right = normalize(cross(forWord, world_Up));
	up = normalize(cross(forWord, right));
}

void Camera::setViewPos(float dir_x, float dir_y) {
	Yaw -= dir_x * 0.001f;
	Pitch -= dir_y * 0.001f;
	updataCameraPos();
}
