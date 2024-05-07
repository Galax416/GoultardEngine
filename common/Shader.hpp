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
private:
    GLuint ID;

public:

	Shader(const char * vertex_file_path,const char * fragment_file_path);// Constructor reads and builds the shader

    void use();
    GLuint getID() { return ID; }
};
