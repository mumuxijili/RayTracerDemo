#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

#include "Shapes.h"
//#include "PointLight.h"

class Color
{
public:
	float r, g, b;
	Color();
	Color(float _r, float _g, float _b);
	virtual ~Color();
	Color add(const Color& c);
	Color multiply(float s) const;
	Color modulate(const Color& c) const;
	Color divide(float d) const;
	void saturate();
	static inline Color black() { return Color(0, 0, 0); }
	static inline Color white() { return Color(1, 1, 1); }
	static inline Color red() { return Color(1, 0, 0); }
	static inline Color green() { return Color(0, 1, 0); }
	static inline Color blue() { return Color(0, 0, 1); }
};

class Ray;
//Base class for materials
class Attribute
{
public:
	Attribute();
	Attribute(float _reflectiveness);
	void setRef(float _reflectiveness);
	float getRef();
	// 采样，光线ray在法向为normal，位置为position的点上的颜色
	virtual Color sample(Ray& ray, glm::vec3& position, glm::vec3& normal);
	virtual ~Attribute();
protected:
	float reflectiveness;
};


//Chess Board Material
class ChessMat : public Attribute
{
public:
	ChessMat();
	ChessMat(float _scale, float _reflectiveness = 0);
	Color sample(Ray& ray, glm::vec3& position, glm::vec3& normal);
	~ChessMat();
private:
	float scale;
};


//temporary global settings
static glm::vec3 lightDir = glm::normalize(glm::vec3(0, 1.5, 1)/*(1, 1, 1)*/); // parallel light
static Color lightColor = Color::white();

//Blinn-Phong Material
class PhongMat : public Attribute
{
public:
	PhongMat();
	PhongMat(const Color& _diffuse, const Color& _specular, float _shininess, bool _usePointLight, glm::vec3 _pointLightPos, Color _pointLightColor, float _reflectiveness = 0.0f);
	PhongMat(const Color& _diffuse, const Color& _specular, float _shininess, float _reflectiveness = 0.0f);
	Color sample(Ray& ray, glm::vec3& position, glm::vec3& normal);
	~PhongMat();
private:
	Color diffuse;
	Color specular;
	float shininess;
	bool usePointLight = false;
	glm::vec3 pointLightPos;
	Color pointLightColor;
};


#endif // __ATTRIBUTE_H__