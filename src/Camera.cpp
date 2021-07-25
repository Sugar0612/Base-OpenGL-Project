#include "Camera.h"

Camera::Camera (vec3 cameraPos, vec3 targetPos, vec3 worldUp): camera_Pos(cameraPos), world_Up(worldUp) {
	forWord = normalize(targetPos - cameraPos);
	right = normalize(cross(forWord, worldUp));
	up = normalize(cross(forWord, right));
}

mat4 Camera::getViewMatrix() {
	return lookAt(camera_Pos, normalize(forWord + camera_Pos), world_Up);
}