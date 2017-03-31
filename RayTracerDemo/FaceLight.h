#ifndef __FACELIGHT_H__
#define __FACELIGHT_H__

#include "Scene.h"

class FaceLight
{
public:
	FaceLight();
	FaceLight(glm::vec3 _position, glm::vec3 _dx, glm::vec3 _dy, Color _color, bool _isShadow);
	~FaceLight();
	Color intersectLight(Scene& scene, CollideInfo info);
	bool isIntersected(Scene& scene, CollideInfo info);
	glm::vec3 randPoint();
	glm::vec3 getPosition();
	glm::vec3 getDx();
	glm::vec3 getDy();
	Color getColor();
private:
	glm::vec3 position;
	glm::vec3 dx, dy;
	Color color;
	bool isShadow;
	//static const int SHADOW_SAMPLE = 10;
};
#endif // __FACELIGHT_H__

