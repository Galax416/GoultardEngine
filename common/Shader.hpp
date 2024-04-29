#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

class Shader {
	public:
    // The program ID
    GLuint ID;
    // Constructor reads and builds the shader
	Shader(const char * vertex_file_path,const char * fragment_file_path);

    // Use the program
    void Use();
};
