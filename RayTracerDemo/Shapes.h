#ifndef __Shapes_H__
#define __Shapes_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>
#include "Attribute.h"

class Ray
{
private:
	glm::vec3 position, direction;
public:
	Ray();
	Ray(glm::vec3 p, glm::vec3 d);
	void setPos(glm::vec3 p);
	void setDirection(glm::vec3 d);
	glm::vec3 getPos();
	glm::vec3 getDirection();
	glm::vec3 getPoint(float t);
	~Ray();
};

class Shape;
class CollideInfo
{
public:
	// 交点法向
	glm::vec3 normal;
	// 交点坐标
	glm::vec3 point;
	// 交点距光源距离
	float distance = -1;
	bool isHit = false;
	Shape* shape;
};

class Attribute;
//Base class of Shapes
class Shape
{
public:
	Attribute* attr;
	Shape();
	virtual CollideInfo collide(Ray ray) = 0;
	virtual ~Shape();
};

class Sphere : public Shape
{
private:
	glm::vec3 position;
	double radius;
public:
	Sphere();
	Sphere(glm::vec3 p, double r);
	Sphere(Sphere& s);
	void setCenter(glm::vec3 c);
	void setRadius(double r);
	glm::vec3 getCenter();
	double getRadius();

	glm::vec3 getNormal(glm::vec3 point);

	CollideInfo collide(Ray ray);
	~Sphere();
};

class Rect : public Shape
{
private:
	// 向量dx和dy表示平面所在的轴，如dx=(10, 0, 0),dy=(0, 0, 10)表示平面与XoZ平面平行，且宽高各为10
	glm::vec3 position, dx, dy;
public:
	Rect();
	Rect(glm::vec3 p, glm::vec3 x, glm::vec3 y);
	Rect(Rect& r);
	void setPosition(glm::vec3 p);
	void setX(glm::vec3 x);
	void setY(glm::vec3 y);
	glm::vec3 getPosition();
	glm::vec3 getX();
	glm::vec3 getY();

	CollideInfo collide(Ray ray);
	~Rect();
};

class Plane : public Shape
{
private:
	glm::vec3 normal;
	glm::vec3 point; //平面上的一点
public:
	Plane();
	Plane(glm::vec3 n, glm::vec3 p);
	glm::vec3 getNormal();
	glm::vec3 getPoint();
	void setNormal(glm::vec3 n);
	void setPoint(glm::vec3 p);

	CollideInfo collide(Ray ray);
	~Plane();
};

#endif // __Shapes_H__
