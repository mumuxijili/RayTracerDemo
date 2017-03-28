#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__
#include "Scene.h"

class PointLight
{
public:
	PointLight();
	PointLight(glm::vec3 _position, Color _color, bool _isShadow);
	Color intersectLight(Scene& scene, CollideInfo info);
	bool isIntersected(Scene& scene, CollideInfo info);
	void setPoint(glm::vec3 _position);
	void setColor(Color _color);
	glm::vec3 getPoint();
	Color getColor();
	~PointLight();
private:
	glm::vec3 position;
	Color color;
	bool isShadow;
};

#endif //__POINTLIGHT_H__

