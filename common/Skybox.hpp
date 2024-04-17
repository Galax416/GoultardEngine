#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>

#include "Camera.hpp"


class Skybox
{
private:
    GLuint m_program_SkyBox;
    GLuint m_cubeMapTexture;
    GLuint m_skyboxVAO;
    GLuint m_skyboxVBO;

    float m_dimSkybox{ 1000.0f };
    
public:
    void init();
    void render(Camera &_camera);
    void clear();
};



#endif