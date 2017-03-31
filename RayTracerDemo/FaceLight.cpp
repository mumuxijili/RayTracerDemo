#include "stdafx.h"
#include "FaceLight.h"


FaceLight::FaceLight()
{
	//
}

FaceLight::FaceLight(glm::vec3 _position, glm::vec3 _dx, glm::vec3 _dy, Color _color, bool _isShadow)
{
	position = _position;
	dx = _dx;
	dy = _dy;
	color = _color;
	isShadow = _isShadow;
}

glm::vec3 FaceLight::getPosition()
{
	return position;
}

glm::vec3 FaceLight::getDx()
{
	return dx;
}

glm::vec3 FaceLight::getDy()
{
	return dy;
}

Color FaceLight::getColor()
{
	return color;
}

glm::vec3 FaceLight::randPoint()
{
	//std::default_random_engine e(time(0));
	std::default_random_engine e(std::random_device{}());
	std::uniform_real_distribution<float> distribution(0.0, 1.0);
	float randx = distribution(e);
	float randy = distribution(e);
	//std::cout << randx << " " << randy << std::endl;
	return glm::vec3(position + randx * dx + randy * dy);
}

// 只考虑光照和阴影，不考虑材质颜色
Color FaceLight::intersectLight(Scene& scene, CollideInfo info)
{
	//Color resultColor = Color::black().add(Color(0.5, 0.5, 0.5));
	Color resultColor = Color::white();
	glm::vec3 tmp = glm::vec3(0);
	for (int i = 0; i < SHADOW_SAMPLE; i++)
	{
		glm::vec3 point2LightRay = randPoint() - info.point;
		float distance = glm::length(point2LightRay);

		Ray shadowRay = Ray(info.point, glm::normalize(point2LightRay));
		glm::vec3 shadowDir = glm::normalize(point2LightRay);

		CollideInfo shadowInfo = scene.collideScene(shadowRay);
		if (shadowInfo.isHit && shadowInfo.distance <= distance) // in the shadow
		{
			//resultColor = resultColor.modulate(Color::shadow());
			//resultColor = resultColor.add(Color::white());
			//resultColor = resultColor.divide(1.1);
			tmp[0] = tmp[0] + 0;
			tmp[1] = tmp[1] + 0;
			tmp[2] = tmp[2] + 0;
		}
		else // compute light strenth
		{
			/*resultColor = this->color.divide(distance * distance);
			float NdotL = glm::dot(info.normal, shadowDir);
			if (NdotL > 0)
			{
				resultColor = resultColor.multiply(NdotL);
				tmp[0] = tmp[0] + resultColor.r * 1000.0f;
				tmp[1] = tmp[1] + resultColor.g * 1000.0f;
				tmp[2] = tmp[2] + resultColor.b * 1000.0f;
			}*/
			tmp[0] = tmp[0] + 1;
			tmp[1] = tmp[1] + 1;
			tmp[2] = tmp[2] + 1;
		}
	}
	resultColor.r = tmp[0] / SHADOW_SAMPLE;
	resultColor.g = tmp[1] / SHADOW_SAMPLE;
	resultColor.b = tmp[2] / SHADOW_SAMPLE;
	return resultColor/*.multiply(500.0f)*/;
	
}

bool FaceLight::isIntersected(Scene& scene, CollideInfo info)
{
	for (int i = 0; i < SHADOW_SAMPLE; i++)
	{
		glm::vec3 point2LightRay = position - info.point;
		float distance = glm::length(point2LightRay);

		Ray shadowRay = Ray(info.point, glm::normalize(point2LightRay));
		glm::vec3 shadowDir = glm::normalize(point2LightRay);

		CollideInfo shadowInfo = scene.collideScene(shadowRay);
		if (shadowInfo.isHit && shadowInfo.distance <= distance)
			return true;
	}
	return false;
}

FaceLight::~FaceLight()
{
	//
}
