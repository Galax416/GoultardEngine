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

#include <glm/glm.hpp>
#include <GL/glew.h>

class Shader {
private:
    // the program ID
    GLuint ID;

public:
    Shader() {};
    // constructor reads and builds the shader
	Shader(const char * vertex_file_path,const char * fragment_file_path);// Constructor reads and builds the shader

    // getter for ID
    GLuint getID() { return ID; }
    
    // use/activate the shader
    void use();

    // utility uniform functions
    void setInt(const std::string &name, int value);
    void setVec3(const std::string &name, const glm::vec3 &value);
    void setMat4(const std::string &name, const glm::mat4 &mat);

};
