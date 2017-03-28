#ifndef __DIRECTLIGHT_H__
#define __DIRECTLIGHT_H__

#include "Scene.h"

class DirectLight
{
private:
	Color color;
	glm::vec3 direction;
	bool isShadow;
public:
	DirectLight();
	DirectLight(Color _color, glm::vec3 _direction, bool _isShadow);
	~DirectLight();
	Color intersectLight(Scene& scene, CollideInfo& info);
};
#endif __DIRECTLIGHT_H__

