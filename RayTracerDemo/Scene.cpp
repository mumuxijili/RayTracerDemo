#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
	//
}


Scene::~Scene()
{
	//
}

void Scene::push(Shape* shape)
{
	items.push_back(shape);
}

CollideInfo Scene::collideScene(Ray ray)
{
	CollideInfo info;
	const float INFINITYFLOAT = 1e30;
	float minDistance = INFINITYFLOAT;
	for (auto &item : items)
	{
		CollideInfo tmpInfo = item->collide(ray);
		if (tmpInfo.isHit && tmpInfo.distance < minDistance)
		{
			minDistance = tmpInfo.distance;
			info = tmpInfo;
		}
	}
	return info;
}