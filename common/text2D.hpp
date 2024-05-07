#pragma once

#include <vector>
#include <cstring>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/stb_image.hpp>
#include <common/Shader.hpp>

GLuint loadTGA_glfw(const char * imagepath);
void initText2D(const char * texturePath, GLuint shaderID);
void printText2D(const char * text, int x, int y, int size);
void cleanupText2D();
