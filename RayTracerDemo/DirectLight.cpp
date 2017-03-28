#include "stdafx.h"
#include "DirectLight.h"


DirectLight::DirectLight()
{
	//
}

DirectLight::DirectLight(Color _color, glm::vec3 _direction, bool _isShadow)
{
	color = _color;
	direction = _direction;
	isShadow = _isShadow;
}

Color DirectLight::intersectLight(Scene& scene, CollideInfo& info)
{
	//产生shadowRay的修正值
	const float k = 1e-4;
	glm::vec3 shadowDir = glm::normalize(-direction);
	Ray shadowRay = Ray(info.point + info.normal * k, shadowDir);
	CollideInfo result = scene.collideScene(shadowRay);
	Color resultColor = Color::black();
	if (isShadow)
	{
		if (result.shape)
		{
			return resultColor;
		}
	}

	//计算光强
	float NdotL = glm::dot(info.normal, shadowRay.getDirection());
	if (NdotL > 0)
	{
		resultColor = resultColor.add(this->color.multiply(NdotL));
	}
	return resultColor;
}

DirectLight::~DirectLight()
{
	//
}
