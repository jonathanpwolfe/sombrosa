#ifndef GAME_ENGINE_CLASS_H
#define GAME_ENGINE_CLASS_H

#include "../glad/gl.h"
#include "shaderClass.h"
#include "VAO.h"
#include"EBO.h"
#include <vector>
#include "ship.h"
#include "asteroid.h"
#include"../GLFW/glfw3.h"

class GameEngine
{
public:
	GameEngine();
   
	void initializeGraphics();
	void close();
	void run();

	// OpenGL specs
	int OPENGL_VERSION_MAJOR = 4;
	int OPENGL_VERSION_MINOR = 6;

	// Variables
	const char* WINDOW_NAME = "SICARIOiDS";
	int WINDOW_WIDTH =1024;
	int WINDOW_HEIGHT =768;
	float CLEAR_RED = 0.0f;
	float CLEAR_GREEN = 0.0f;
	float CLEAR_BLUE = 0.0f;
	float CLEAR_ALPHA = 1.0f;
	GLFWwindow *window;
   std::vector<VAO> VAOs;
    std::vector<VBO> VBOs;
    std::vector<EBO> EBOs;
    GLuint uniID;
    GLuint uniID2;
	std::vector<Shader> shaders;
	Ship ship;
	std::vector<Asteroid> asteroids;
};

#endif