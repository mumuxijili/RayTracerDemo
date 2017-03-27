#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	//
}

Camera::Camera(glm::vec3 _position, glm::vec3 _front, glm::vec3 _refup, float _fov)
{
	position = _position;
	front = _front;
	refup = _refup;
	fov = _fov;
	right = glm::normalize(glm::cross(front, refup));
	up = glm::normalize(glm::cross(right, front));
	// 假设position到投影平面的距离是1?
	// 长宽一致
	fovscale = tan(fov * glm::pi<float>() / 180.0f);
	//std::cout << fovscale << std::endl;
}

Ray Camera::getRay(float x, float y)
{
	// 把x[0, 1]映射到sx[-1, 1]
	glm::vec3 r = right * (((x - 0.5f) * 2 * fovscale));
	glm::vec3 u = up * (((y - 0.5f) * 2 * fovscale));
	glm::vec3 dir = glm::normalize(front + r + u);
	//std::cout << dir[0] << " " << dir[1] << " " << dir[2] << std::endl;
	return Ray(position, dir);
}

Camera::~Camera()
{
	//
}

