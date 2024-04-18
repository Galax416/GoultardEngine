#include "Skybox.hpp"
#include "shader.hpp"
#include "texture.hpp"

#include <vector>
#include <string>

void Skybox::init()
{
    m_program_SkyBox = LoadShaders("../main/vertexSky.glsl", "../main/fragmentSky.glsl");

    std::vector<std::string> faces = {
		"../data/skybox/right.jpg",
		"../data/skybox/left.jpg",
		"../data/skybox/top.jpg",
		"../data/skybox/bottom.jpg",
		"../data/skybox/front.jpg",
		"../data/skybox/back.jpg"
	};

    float skyboxVertices[] = {
		// positions          
		-m_dimSkybox,  m_dimSkybox, -m_dimSkybox,
		-m_dimSkybox, -m_dimSkybox, -m_dimSkybox,
		m_dimSkybox, -m_dimSkybox, -m_dimSkybox,
		m_dimSkybox, -m_dimSkybox, -m_dimSkybox,
		m_dimSkybox,  m_dimSkybox, -m_dimSkybox,
		-m_dimSkybox,  m_dimSkybox, -m_dimSkybox,

		-m_dimSkybox, -m_dimSkybox,  m_dimSkybox,
		-m_dimSkybox, -m_dimSkybox, -m_dimSkybox,
		-m_dimSkybox,  m_dimSkybox, -m_dimSkybox,
		-m_dimSkybox,  m_dimSkybox, -m_dimSkybox,
		-m_dimSkybox,  m_dimSkybox,  m_dimSkybox,
		-m_dimSkybox, -m_dimSkybox,  m_dimSkybox,

		m_dimSkybox, -m_dimSkybox, -m_dimSkybox,
		m_dimSkybox, -m_dimSkybox,  m_dimSkybox,
		m_dimSkybox,  m_dimSkybox,  m_dimSkybox,
		m_dimSkybox,  m_dimSkybox,  m_dimSkybox,
		m_dimSkybox,  m_dimSkybox, -m_dimSkybox,
		m_dimSkybox, -m_dimSkybox, -m_dimSkybox,

		-m_dimSkybox, -m_dimSkybox,  m_dimSkybox,
		-m_dimSkybox,  m_dimSkybox,  m_dimSkybox,
		m_dimSkybox,  m_dimSkybox,  m_dimSkybox,
		m_dimSkybox,  m_dimSkybox,  m_dimSkybox,
		m_dimSkybox, -m_dimSkybox,  m_dimSkybox,
		-m_dimSkybox, -m_dimSkybox,  m_dimSkybox,

		-m_dimSkybox,  m_dimSkybox, -m_dimSkybox,
		m_dimSkybox,  m_dimSkybox, -m_dimSkybox,
		m_dimSkybox,  m_dimSkybox,  m_dimSkybox,
		m_dimSkybox,  m_dimSkybox,  m_dimSkybox,
		-m_dimSkybox,  m_dimSkybox,  m_dimSkybox,
		-m_dimSkybox,  m_dimSkybox, -m_dimSkybox,

		-m_dimSkybox, -m_dimSkybox, -m_dimSkybox,
		-m_dimSkybox, -m_dimSkybox,  m_dimSkybox,
		m_dimSkybox, -m_dimSkybox, -m_dimSkybox,
		m_dimSkybox, -m_dimSkybox, -m_dimSkybox,
		-m_dimSkybox, -m_dimSkybox,  m_dimSkybox,
		m_dimSkybox, -m_dimSkybox,  m_dimSkybox
	};

    m_cubeMapTexture = loadCubeMapTexture(faces);

    // Création du VAO et du VBO
	glGenVertexArrays(1, &m_skyboxVAO);
	glGenBuffers(1, &m_skyboxVBO);
	
	// Liaison du VAO
	glBindVertexArray(m_skyboxVAO);

	// Liaison du VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void Skybox::render(Camera &_camera)
{
	glm::mat4 viewMatrix = _camera.getViewMatrix();
	glm::mat4 projectionMatrix = _camera.getProjectionMatrix();
	glm::mat4 modelMatrix/*  = glm::mat4(1.0) */;

	glUseProgram(m_program_SkyBox);
    glDepthFunc(GL_LEQUAL);
    glBindVertexArray(m_skyboxVAO);
    if (m_cubeMapTexture != -1){

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMapTexture);
        glUniform1i(glGetUniformLocation(m_program_SkyBox, "Skybox"), 0);
		glUniformMatrix4fv(glGetUniformLocation(m_program_SkyBox, "Model"), 1, GL_FALSE, &modelMatrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_program_SkyBox, "View"), 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_program_SkyBox, "Projection"), 1, GL_FALSE, &projectionMatrix[0][0]);

    }
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}

void Skybox::clear()
{
	// Cleanup VAO and VBO 
    glDeleteBuffers(1, &m_skyboxVBO);
    glDeleteVertexArrays(1, &m_skyboxVAO);

    // Cleanup programme
    glDeleteProgram(m_program_SkyBox);
}