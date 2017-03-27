#ifndef __Camera_H__
#define __Camera_H__

#include "Shapes.h"

class Camera
{
private:
	glm::vec3 position, front, right, up, refup;
	float fov, fovscale;
public:
	Camera();
	Camera(glm::vec3 _position, glm::vec3 _front, glm::vec3 _refup, float _fov);
	Ray getRay(float sx, float sy);
	~Camera();
};
#endif // __Camera_H__

