#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

#include "Shapes.h"
#include <random>
#include <ctime>

#define SHADOW_SAMPLE 10

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
	static inline Color shadow() { return Color(0.2, 0.2, 0.2); }
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
	// ����������ray�ڷ���Ϊnormal��λ��Ϊposition�ĵ��ϵ���ɫ
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
	//pointLight
	PhongMat(const Color& _diffuse, const Color& _specular, float _shininess, bool _usePointLight, glm::vec3 _pointLightPos, Color _pointLightColor, float _reflectiveness = 0.0f);
	//directLight
	PhongMat(const Color& _diffuse, const Color& _specular, float _shininess, float _reflectiveness = 0.0f);
	//faceLight
	PhongMat(const Color& _diffuse, const Color& _specular, float _shininess, bool _useFaceLight, glm::vec3 _faceLightPos, Color _faceLightColor, glm::vec3 _dx, glm::vec3 _dy, float _reflectiveness = 0.0f);
	glm::vec3 randPoint();
	Color sample(Ray& ray, glm::vec3& position, glm::vec3& normal);
	~PhongMat();
private:
	Color diffuse;
	Color specular;
	float shininess;
	bool usePointLight = false;
	glm::vec3 pointLightPos;
	Color pointLightColor;
	bool useFaceLight = false;
	glm::vec3 faceLightPos;
	glm::vec3 dx;
	glm::vec3 dy;
	Color faceLightColor;
};


#endif // __ATTRIBUTE_H__