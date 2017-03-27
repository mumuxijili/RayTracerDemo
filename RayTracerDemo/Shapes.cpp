#include "stdafx.h"
#include "Shapes.h"

// Ray
Ray::Ray()
{
	//
}

Ray::~Ray()
{
	//
}

Ray::Ray(glm::vec3 p, glm::vec3 d)
{
	position = p;
	direction = d;
}

void Ray::setPos(glm::vec3 p)
{
	position = p;
}

void Ray::setDirection(glm::vec3 d)
{
	direction = d;
}

glm::vec3 Ray::getPos()
{
	return position;
}

glm::vec3 Ray::getDirection()
{
	return direction;
}

glm::vec3 Ray::getPoint(float t)
{
	return position + direction * t;
}


//Shape
Shape::Shape()
{
	//
}

Shape::~Shape()
{
	//
}


//Sphere
Sphere::Sphere()
{
	//
}

Sphere::~Sphere()
{
	//
}

Sphere::Sphere(glm::vec3 p, double r)
{
	position = p;
	radius = r;
}

Sphere::Sphere(Sphere& s)
{
	position = s.getCenter();
	radius = s.getRadius();
}

void Sphere::setCenter(glm::vec3 c)
{
	position = c;
}

void Sphere::setRadius(double r)
{
	radius = r;
}

glm::vec3 Sphere::getCenter()
{
	return position;
}

double Sphere::getRadius()
{
	return radius;
}

glm::vec3 Sphere::getNormal(glm::vec3 point)
{
	return glm::normalize(point - position);
}

CollideInfo Sphere::collide(Ray ray)
{
	CollideInfo info;
	glm::vec3 v = ray.getPos() - position;
	float DdotV = glm::dot(ray.getDirection(), v);
	if (DdotV > 0) return info;


	if ((DdotV * DdotV) - glm::dot(v, v) + (radius * radius) >= 0)
	{
		info.isHit = true;
		info.shape = this;
		info.distance = -DdotV - sqrt(DdotV * DdotV - glm::dot(v, v) + radius * radius);
		info.point = ray.getPoint(info.distance);
		info.normal = glm::normalize(info.point - position);
	}
	return info;
}


//Rect
Rect::Rect()
{
	//
}

Rect::~Rect()
{
	//
}

Rect::Rect(glm::vec3 p, glm::vec3 x, glm::vec3 y)
{
	position = p;
	dx = x;
	dy = y;
}

Rect::Rect(Rect& r)
{
	position = r.getPosition();
	dx = r.getX();
	dy = r.getY();
}

void Rect::setPosition(glm::vec3 p)
{
	position = p;
}

void Rect::setX(glm::vec3 x)
{
	dx = x;
}

void Rect::setY(glm::vec3 y)
{
	dy = y;
}

glm::vec3 Rect::getPosition()
{
	return position;
}

glm::vec3 Rect::getX()
{
	return dx;
}

glm::vec3 Rect::getY()
{
	return dy;
}

CollideInfo Rect::collide(Ray ray)
{
	CollideInfo info;
	return info;
}


//Plane
Plane::Plane()
{
	//
}

Plane::~Plane()
{
	//
}

Plane::Plane(glm::vec3 n, glm::vec3 p)
{
	normal = n;
	point = p;
}

void Plane::setNormal(glm::vec3 n)
{
	normal = n;
}

void Plane::setPoint(glm::vec3 p)
{
	point = p;
}

glm::vec3 Plane::getNormal()
{
	return normal;
}

glm::vec3 Plane::getPoint()
{
	return point;
}

CollideInfo Plane::collide(Ray ray)
{
	CollideInfo info;
	float a = glm::dot(ray.getDirection(), normal);
	if (a < 0)
	{
		info.isHit = true;
		info.shape = this;
		info.normal = normal;
		float b = glm::dot((point - ray.getPos()), normal);
		info.distance = b / a;
		info.point = ray.getPoint(info.distance);
	}
	return info;
}