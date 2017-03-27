#include "stdafx.h"
#include "Attribute.h"
#include <algorithm>

//Color
Color::Color()
{
	//
}

Color::Color(float _r, float _g, float _b)
{
	r = _r;
	g = _g;
	b = _b;
}

Color Color::add(const Color& c)
{
	Color t = Color(r + c.r, g + c.g, b + c.b);
	t.saturate();
	return t;
}

Color Color::multiply(float s) const
{
	Color t = Color(r * s, g * s, b * s);
	t.saturate();
	return t;
}

Color Color::modulate(const Color& c) const
{
	Color t = Color(r * c.r, g * c.g, b * c.b);
	t.saturate();
	return t;
}

void Color::saturate()
{
	r = r > 1.0f ? 1.0f : r;
	g = g > 1.0f ? 1.0f : g;
	b = b > 1.0f ? 1.0f : b;
}

Color::~Color()
{
	//
}


//Attribute
Attribute::Attribute()
{
	//
}

Attribute::Attribute(float _reflectiveness)
{
	reflectiveness = _reflectiveness;
}

void Attribute::setRef(float _reflectiveness)
{
	reflectiveness = _reflectiveness;
}

float Attribute::getRef()
{
	return reflectiveness;
}

Color Attribute::sample(Ray& ray, glm::vec3& position, glm::vec3& normal)
{
	std::cout << "this is base" << std::endl;
	return  Color(0, 0, 0);
}

Attribute::~Attribute()
{
	//
}


//Chess Board Material
ChessMat::ChessMat()
{
	//
}

ChessMat::~ChessMat()
{
	//
}

ChessMat::ChessMat(float _scale, float _reflectiveness /* = 0.0f */)
{
	scale = _scale;
	reflectiveness = _reflectiveness;
}

Color ChessMat::sample(Ray& ray, glm::vec3& position, glm::vec3& normal)
{
	float d = abs(floor(position.x * scale) + floor(position.z * scale));
	d = fmod(d, 2);
	return d < 1 ? Color::black() : Color::white();
}


//Blinn-Phong Material
PhongMat::PhongMat()
{
	//
}

PhongMat::~PhongMat()
{
	//
}

PhongMat::PhongMat(const Color& _diffuse, const Color& _specular, float _shininess, float _reflectiveness /* = 0.0f */)
{
	diffuse = _diffuse;
	specular = _specular;
	shininess = _shininess;
	reflectiveness = _reflectiveness;
}

Color PhongMat::sample(Ray& ray, glm::vec3& position, glm::vec3& normal)
{
	float NdotL = glm::dot(normal, lightDir);
	glm::vec3 H = glm::normalize(lightDir - ray.getDirection());
	float NdotH = glm::dot(normal, H);
	Color diffuseTerm = diffuse.multiply(std::max<float>(NdotL, 0.0f));
	Color specularTerm = specular.multiply(std::powf(std::max<float>(NdotH, 0.0f), shininess));
	return lightColor.modulate(diffuseTerm.add(specularTerm));
}