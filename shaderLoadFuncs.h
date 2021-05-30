#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool readShaderSource(const char* name, std::vector<GLchar>& buffer);
GLuint createProgram(const char* vsrc, const char* fsrc);
GLuint loadProgram(const char* vert, const char* frag);