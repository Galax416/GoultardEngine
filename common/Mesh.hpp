#include <iostream>
#include <vector>
#include <common/stb_image.h>
#include <string>
#include <glm/glm.hpp>
#include <common/objloader.hpp>
#include <GL/glew.h>

class Mesh {
private:
    // Geometry
    std::vector<unsigned short> indices;
    std::vector<std::vector<unsigned short> > triangles; 
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> indexed_uvs;

    GLuint texture; // Texture
    glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f); // Color

    // VBO & ID
    GLuint vertexbuffer;
    GLuint elementbuffer;
    GLuint uvbuffer;

    GLuint textureID;
    GLuint colorID;
public:

    Mesh(std::string filename) {
        loadOFF(filename, indexed_vertices, indices, triangles );
    }

    Mesh(std::vector<unsigned short>& indices,
         std::vector<glm::vec3>& indexed_vertices,
         std::vector<glm::vec2>& indexed_uvs) {
        this->indices = indices;
        this->indexed_vertices = indexed_vertices;
        this->indexed_uvs = indexed_uvs;
    }
    Mesh() {}

    std::vector<unsigned short> getIndices() {
        return indices;
    }
    std::vector<std::vector<unsigned short> > getTriangles() {
        return triangles;
    }
    std::vector<glm::vec3> getIndexedVertices() {
        return indexed_vertices;
    }
    glm::vec3 getIndexedVertices(int index) {
        return indexed_vertices.at(index);
    }
    std::vector<glm::vec2> getIndexedUvs() {
        return indexed_uvs;
    }

    void setIndexedVertices(glm::vec3 vertices, int index) {
        indexed_vertices.at(index) = vertices;
    }

    void setTexture(std::string filename) {
        this->texture = loadTexture2DFromFilePath(filename);
    }
    void setcolor(glm::vec3 color) {
		this->color = color;
	}

    void bindVBO(GLuint programID) {
        // Load it into a VBO
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

        // Generate a buffer for the indices as well
        glGenBuffers(1, &elementbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

        // Generate a buffer for UVs
        glGenBuffers(1, &uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

        // Load the texture
        textureID = glGetUniformLocation(programID, "textureSampler");
        colorID = glGetUniformLocation(programID, "colorSampler");
    }

    void render() {
        // Bind our texture in Texture Unit 0
        if (texture != -1) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glUniform1i(textureID, 0);
        }
        if (colorID != -1) glUniform3fv(colorID, 1, &color[0]); // Color

        // Bind UVs
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
        
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                    0,                  // attribute
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
                    );

        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

        // Draw the triangles !
        glDrawElements(
                    GL_TRIANGLES,      // mode
                    indices.size(),    // count
                    GL_UNSIGNED_SHORT,   // type
                    (void*)0           // element array buffer offset
                    );

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

    }

    void unbindVBO() {
        // Cleanup VBO and shader
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteBuffers(1, &elementbuffer);
        glDeleteBuffers(1, &uvbuffer);
    }
};