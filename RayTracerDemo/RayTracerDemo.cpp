// RayTracerDemo.cpp : Defines the entry point for the console application.
// http://blog.csdn.net/silangquan/article/details/8176855
#define GLFW_INCLUDE_GLU
#define GLFW_DLL
#include "stdafx.h"
#include <GLFW/glfw3.h>
//#include <GL/glew.h>
#include <iostream>
#include <cmath>
#include "Shapes.h"
#include "Camera.h"
#include "Scene.h"
#include "Shader.h"
#include <windows.h>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

using namespace std;

GLFWwindow* window;
vector<vector<cv::Vec3b>> image;


void initScene()
{
	glShadeModel(GL_SMOOTH);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// 告诉系统对透视进行修正
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, GLint(width), GLint(height));
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(45.0f, (GLint)width / (GLint)height, 0.1f, 100.0f);
	glm::mat4 projection = glm::perspective(45.0f, (float)(width / height), 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(projection));
	//glLoadIdentity();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key) {
	case GLFW_KEY_ESCAPE: //Escape key
		exit(0); //Exit the program
	}
}

void drawcall()
{
	long maxDepth = 20;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-0.5f, -0.5f, -1.0f);
	glBegin(GL_POINTS);
	glPointSize(2.0f);
	double dx = 1.0f / WINDOW_WIDTH;
	double dy = 1.0f / WINDOW_HEIGHT;
	double dd = 255.0f / maxDepth;
	image.clear();
	image.resize(WINDOW_HEIGHT, std::vector<cv::Vec3b>(WINDOW_WIDTH));
	for (long y = 0; y < WINDOW_HEIGHT; y++)
	{
		// sample x, sample y（取样坐标）
		double sy = 1 - dy * y;
		for (long x = 0; x < WINDOW_WIDTH; x++)
		{
			double sx = dx * x;
			float colorR = x * 1.0 / WINDOW_WIDTH * 255.0;
			float colorB = y * 1.0 / WINDOW_HEIGHT * 255.0;
			glColor3f(colorR / 255.0f, 0.0f, colorB / 255.0f);
			glVertex2f(sx, sy);
			image[y][x] = cv::Vec3b(colorB, 0.0f, colorR);
		}
	}
	glEnd();

	glBegin(GL_POINTS);
	glPointSize(5.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	glEnd();
	glFlush();
	glfwSwapBuffers(window);
}

void renderASphere()
{
	long maxDepth = 18;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glTranslatef(-0.5f, -0.5f, -1.0f);
	Sphere* sphere1 = new Sphere(glm::vec3(0, 10, -10), 10);
	Camera camera(glm::vec3(0, 10, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 60.0f);
	glBegin(GL_POINTS);
	glPointSize(2.0f);
	double dx = 1.0f / WINDOW_WIDTH;
	double dy = 1.0f / WINDOW_HEIGHT;
	double dd = 255.0f / maxDepth;
	image.clear();
	image.resize(WINDOW_HEIGHT, std::vector<cv::Vec3b>(WINDOW_WIDTH));
	for (long y = 0; y < WINDOW_HEIGHT; y++)
	{
		// sample x, sample y（取样坐标）
		double sy = 1 - dy * y;
		for (long x = 0; x < WINDOW_WIDTH; x++)
		{
			double sx = dx * x;
			Ray ray = Ray(camera.getRay(sx, sy));
			CollideInfo info = sphere1->collide(ray);
			if (info.isHit)
			{
				double d = MIN(info.distance * dd, 255);
				int depth = (int)255 - d;
				glColor3ub(depth, depth, depth);
				//glColor3ub(128 * (info.normal.x + 1), 128 * (info.normal.y + 1), 128 * (info.normal.z + 1));
				glVertex2f(sx, sy);
				image[y][x] = cv::Vec3b(depth, depth, depth);
				//image[y][x] = cv::Vec3b(128 * (info.normal.z + 1), 128 * (info.normal.y + 1), 128 * (info.normal.x + 1));
			}
			else
			{
				image[y][x] = cv::Vec3b(0, 0, 0);
			}
		}
	}
	glEnd();

	glFlush();
	glfwSwapBuffers(window);
}

void renderAPlane()
{
	long maxDepth = 18;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-0.5f, -0.5f, -1.0f);
	//Sphere* shape1 = new Sphere(glm::vec3(0, 10, -10), 10);
	Plane* shape1 = new Plane(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0));
	Camera camera(glm::vec3(0, 10, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 60.0f);
	glBegin(GL_POINTS);
	glPointSize(2.0f);
	double dx = 1.0f / WINDOW_WIDTH;
	double dy = 1.0f / WINDOW_HEIGHT;
	double dd = 255.0f / maxDepth;
	image.clear();
	image.resize(WINDOW_HEIGHT, std::vector<cv::Vec3b>(WINDOW_WIDTH));
	for (long y = 0; y < WINDOW_HEIGHT; y++)
	{
		// sample x, sample y（取样坐标）
		double sy = 1 - dy * y;
		for (long x = 0; x < WINDOW_WIDTH; x++)
		{
			double sx = dx * x;
			Ray ray = Ray(camera.getRay(sx, sy));
			CollideInfo info = shape1->collide(ray);
			if (info.isHit)
			{
				double d = MIN(info.distance * dd, 255);
				int depth = (int)255 - d;
				glColor3ub(depth, depth, depth);
				//glColor3ub(128 * (info.normal.x + 1), 128 * (info.normal.y + 1), 128 * (info.normal.z + 1));
				glVertex2f(sx, sy);
				image[y][x] = cv::Vec3b(depth, depth, depth);
				//image[y][x] = cv::Vec3b(128 * (info.normal.z + 1), 128 * (info.normal.y + 1), 128 * (info.normal.x + 1));
			}
			else
			{
				image[y][x] = cv::Vec3b(0, 0, 0);
			}
		}
	}
	glEnd();

	glFlush();
	glfwSwapBuffers(window);
}

void renderAScene()
{
	long maxDepth = 18;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-0.5f, -0.5f, -1.0f);
	Sphere* sphere1 = new Sphere(glm::vec3(0, 10, -10), 10);
	Sphere* sphere2 = new Sphere(glm::vec3(0, 5, 2), 2);
	Plane* plane1 = new Plane(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0));
	plane1->attr = new ChessMat(0.1f);
	sphere1->attr = new PhongMat(Color::red(), Color::white(), 16.0f);
	sphere2->attr = new PhongMat(Color::blue(), Color::white(), 8.0f);
	Scene scene;
	scene.push(sphere1);
	scene.push(sphere2);
	scene.push(plane1);
	Camera camera(glm::vec3(0, 5, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 60.0f);
	glBegin(GL_POINTS);
	glPointSize(2.0f);
	double dx = 1.0f / WINDOW_WIDTH;
	double dy = 1.0f / WINDOW_HEIGHT;
	double dd = 255.0f / maxDepth;
	image.clear();
	image.resize(WINDOW_HEIGHT, std::vector<cv::Vec3b>(WINDOW_WIDTH));
	for (long y = 0; y < WINDOW_HEIGHT; y++)
	{
		// sample x, sample y（取样坐标）
		double sy = 1 - dy * y;
		for (long x = 0; x < WINDOW_WIDTH; x++)
		{
			double sx = dx * x;
			Ray ray = Ray(camera.getRay(sx, sy));
			CollideInfo info = scene.collideScene(ray);
			if (info.isHit)
			{
				Color color = info.shape->attr->sample(ray, info.point, info.normal);
				glColor3ub(color.r * 255, color.g * 255, color.b * 255);
				glVertex2f(sx, sy);
				image[y][x] = cv::Vec3b(color.b * 255, color.g * 255, color.r * 255);
			}
			else
			{
				image[y][x] = cv::Vec3b(0, 0, 0);
			}
		}
	}
	glEnd();

	glFlush();
	glfwSwapBuffers(window);
}

Color rayTracer(Scene* scene, Ray& ray, long maxReflect)
{
	CollideInfo info = scene->collideScene(ray);
	if (info.isHit)
	{
		float reflectiveness = info.shape->attr->getRef();
		Color color = info.shape->attr->sample(ray, info.point, info.normal);
		color = color.multiply(1 - reflectiveness);

		if (reflectiveness > 0 && maxReflect > 0)
		{
			glm::vec3 r = info.normal * (-2 * glm::dot(info.normal, ray.getDirection())) + ray.getDirection();
			Ray ray2 = Ray(info.point, r);
			Color reflectColor = rayTracer(scene, ray2, maxReflect - 1);
			color = color.add(reflectColor.multiply(reflectiveness));
		}
		return color;
	}
	else
		return Color::black();
}

void renderASceneRecursive()
{
	long maxDepth = 18;
	long maxReflect = 5;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-0.5f, -0.5f, -1.0f);
	Sphere* sphere1 = new Sphere(glm::vec3(0, 10, -10), 10);
	Sphere* sphere2 = new Sphere(glm::vec3(15, 5, -10), 5);
	Plane* plane1 = new Plane(glm::vec3(0, 1, 0), glm::vec3(0, 0, 0));
	plane1->attr = new ChessMat(0.1f, 0.5f);
	sphere1->attr = new PhongMat(Color::red(), Color::white(), 32.0f, 0.25f);
	sphere2->attr = new PhongMat(Color::blue(), Color::white(), 8.0f, 0.25f);
	Scene scene;
	scene.push(sphere1);
	scene.push(sphere2);
	scene.push(plane1);
	Camera camera(glm::vec3(0, 15, 10), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 60.0f);
	glBegin(GL_POINTS);
	glPointSize(2.0f);
	double dx = 1.0f / WINDOW_WIDTH;
	double dy = 1.0f / WINDOW_HEIGHT;
	double dd = 255.0f / maxDepth;
	image.clear();
	image.resize(WINDOW_HEIGHT, std::vector<cv::Vec3b>(WINDOW_WIDTH));
	for (long y = 0; y < WINDOW_HEIGHT; y++)
	{
		// sample x, sample y（取样坐标）
		double sy = 1 - dy * y;
		for (long x = 0; x < WINDOW_WIDTH; x++)
		{
			double sx = dx * x;
			Ray ray = Ray(camera.getRay(sx, sy));
			CollideInfo info = scene.collideScene(ray);
			if (info.isHit)
			{
				Color color = rayTracer(&scene, ray, maxReflect);
				glColor3ub(color.r * 255, color.g * 255, color.b * 255);
				glVertex2f(sx, sy);
				image[y][x] = cv::Vec3b(color.b * 255, color.g * 255, color.r * 255);
			}
			else
			{
				image[y][x] = cv::Vec3b(0, 0, 0);
			}
		}
	}
	glEnd();

	glBegin(GL_POINTS);
	glPointSize(5.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	glEnd();

	glFlush();
	glfwSwapBuffers(window);
}

void saveimage(string filename)
{
	int h = (int)image.size();
	int w = (int)image[0].size();
	cv::Mat out(h, w, CV_8UC3);
	for (auto i = 0; i < h; i++)
	{
		for (auto j = 0; j < w; j++)
		{
			out.at<cv::Vec3b>(i, j) = image[i][j];
		}
	}
	imwrite(filename, out);
}

// fps counter
void _update_fps_counter(GLFWwindow* window) {
	static double previous_seconds = glfwGetTime();
	static int frame_count;
	double current_seconds = glfwGetTime();
	double elapsed_seconds = current_seconds - previous_seconds;
	if (elapsed_seconds > 0.25) {
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[128];
		sprintf(tmp, "Ray Tracer Demo @ FPS: %.2f", fps);
		glfwSetWindowTitle(window, tmp);
		frame_count = 0;
	}
	frame_count++;
}

int main()
{
	// init GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Ray Tracer Demo", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	initScene();
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, key_callback);

	// init glew(Shader program starts from here)
	/*glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("Shaders/SimpleVertexShader.vert", "Shaders/SimpleFragmentShader.frag");

	vector<glm::vec3> vertices;
	vector<glm::vec3> colors;

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	GLuint colorBuffers;
	glGenBuffers(1, &colorBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffers);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);*/

	do
	{
		_update_fps_counter(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawcall();
		//renderASphere();
		//renderAPlane();
		//renderAScene();
		//renderASceneRecursive();
		glfwPollEvents();
		//system("pause");
	}while( glfwWindowShouldClose(window) == 0 );

	//saveimage("10.bmp");
	//system("pause");
	glfwTerminate();
    return 0;
}

