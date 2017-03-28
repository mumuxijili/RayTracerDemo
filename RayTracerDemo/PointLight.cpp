#include "stdafx.h"
#include "PointLight.h"


PointLight::PointLight()
{
	//
}

PointLight::PointLight(glm::vec3 _position, Color _color, bool _isShadow)
{
	position = _position;
	color = _color;
	isShadow = _isShadow;
}

Color PointLight::intersectLight(Scene& scene, CollideInfo info)
{
	glm::vec3 point2LightRay = position - info.point;
	float distance = glm::length(point2LightRay);

	Ray shadowRay = Ray(info.point, glm::normalize(point2LightRay));
	glm::vec3 shadowDir = glm::normalize(point2LightRay);

	CollideInfo shadowInfo = scene.collideScene(shadowRay);
	Color resultColor = Color::black().multiply(0.5f);
	if (shadowInfo.isHit && shadowInfo.distance <= distance)
	{
		return resultColor;
	}
	else
	{
		resultColor = this->color.divide(distance * distance);
		float NdotL = glm::dot(info.normal, shadowDir);
		if (NdotL > 0)
		{
			resultColor = resultColor.multiply(NdotL);
		}
		return resultColor;
	}
}

bool PointLight::isIntersected(Scene& scene, CollideInfo info)
{
	glm::vec3 point2LightRay = position - info.point;
	float distance = glm::length(point2LightRay);

	Ray shadowRay = Ray(info.point, glm::normalize(point2LightRay));
	glm::vec3 shadowDir = glm::normalize(point2LightRay);

	CollideInfo shadowInfo = scene.collideScene(shadowRay);
	if (shadowInfo.isHit && shadowInfo.distance <= distance)
		return true;
	else
		return false;
}

void PointLight::setColor(Color _color)
{
	color = _color;
}

void PointLight::setPoint(glm::vec3 _position)
{
	position = _position;
}

glm::vec3 PointLight::getPoint()
{
	return position;
}

Color PointLight::getColor()
{
	return color;
}

PointLight::~PointLight()
{
	//
}
