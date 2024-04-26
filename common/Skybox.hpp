#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>

#include <common/Camera.hpp>
#include <common/Model.hpp>
#include <common/Shader.hpp>

#include <vector>
#include <string>

GLuint loadCubeMapTexture(std::vector<std::string> faces);

class Skybox
{
private:
    GLuint m_program_SkyBox;
    GLuint m_cubeMapTexture;
    GLuint m_skyboxVAO;
    GLuint m_skyboxVBO;

    float m_dimSkybox{ 1000.0f };
    
public:
    void init(Shader _shader);
    void render(Camera &_camera);
    void clear();
};