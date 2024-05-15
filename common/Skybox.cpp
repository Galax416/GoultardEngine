#include <common/Skybox.hpp>

Skybox::Skybox(Shader *_shader) : shader(_shader) {

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
	glm::mat4 modelMatrix = glm::mat4(1.0);

	shader->use();
    glDepthFunc(GL_LEQUAL);
    glBindVertexArray(m_skyboxVAO);
    if (m_cubeMapTexture != -1){

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMapTexture);
		shader->setInt("Skybox", 0);
		shader->setMat4("Model", modelMatrix);
		shader->setMat4("View", viewMatrix);
		shader->setMat4("Projection", projectionMatrix);

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
    glDeleteProgram(shader->getID());
}

GLuint loadCubeMapTexture(std::vector<std::string> faces) {
	GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            throw std::runtime_error("Cubemap tex failed to load at path: " + faces[i]);
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}