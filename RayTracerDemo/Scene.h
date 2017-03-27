#ifndef __Scene_H__
#define  __Scene_H__

#include "Shapes.h"
#include <vector>

class Scene
{
private:
	std::vector<Shape*> items;
public:
	Scene();
	~Scene();
	void push(Shape* shape);
	CollideInfo collideScene(Ray ray);
};
#endif // __Scene_H__

