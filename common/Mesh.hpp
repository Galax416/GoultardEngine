#pragma once

#include <common/Shader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class AABB {
public:
    glm::vec3 boxMin = glm::vec3(std::numeric_limits<float>::infinity());
    glm::vec3 boxMax = glm::vec3(-std::numeric_limits<float>::infinity());

public:
    bool intersects(const AABB& other) const {
        // Vérifier s'il n'y a pas de collision sur un des axes (X, Y, Z)
        bool noCollisionOnX = boxMax.x < other.boxMin.x || boxMin.x > other.boxMax.x;
        bool noCollisionOnY = boxMax.y < other.boxMin.y || boxMin.y > other.boxMax.y;
        bool noCollisionOnZ = boxMax.z < other.boxMin.z || boxMin.z > other.boxMax.z;

        // S'il n'y a pas de collision sur l'un des axes, alors il n'y a pas de collision
        return !(noCollisionOnX || noCollisionOnY || noCollisionOnZ);
    }

    void computeBoundingBox(std::vector<Vertex> vertices) {
        // Initialize minCoords and maxCoords with the position of the first vertex
        glm::vec3 minCoords = vertices[0].Position;
        glm::vec3 maxCoords = vertices[0].Position;

        // Iterate over all vertices to find the minimum and maximum coordinates
        for (const auto& vertex : vertices) {
            minCoords.x = std::min(minCoords.x, vertex.Position.x);
            minCoords.y = std::min(minCoords.y, vertex.Position.y);
            minCoords.z = std::min(minCoords.z, vertex.Position.z);

            maxCoords.x = std::max(maxCoords.x, vertex.Position.x);
            maxCoords.y = std::max(maxCoords.y, vertex.Position.y);
            maxCoords.z = std::max(maxCoords.z, vertex.Position.z);
        }

        // Expand the bounding box slightly for safety margin
        this->boxMin = minCoords * 1.02f;
        this->boxMax = maxCoords * 1.02f;
    }

    void updateBoundingBox(const glm::mat4& modelMatrix) {
        glm::vec3 transformedMin = glm::vec3(modelMatrix * glm::vec4(boxMin, 1.0f));
        glm::vec3 transformedMax = glm::vec3(modelMatrix * glm::vec4(boxMax, 1.0f));

        boxMin = glm::min(transformedMin, transformedMax);
        boxMax = glm::max(transformedMin, transformedMax);
    }

    void expand(const AABB& other) {
        // Mettre à jour les coordonnées minimales
        boxMin.x = std::min(boxMin.x, other.boxMin.x);
        boxMin.y = std::min(boxMin.y, other.boxMin.y);
        boxMin.z = std::min(boxMin.z, other.boxMin.z);

        // Mettre à jour les coordonnées maximales
        boxMax.x = std::max(boxMax.x, other.boxMax.x);
        boxMax.y = std::max(boxMax.y, other.boxMax.y);
        boxMax.z = std::max(boxMax.z, other.boxMax.z);
    }

    glm::vec3 getNormalCollision(const AABB& other) const {
        // Calculate the center of both AABBs
        glm::vec3 centerPlayer = (boxMin + boxMax) * 0.5f;
        glm::vec3 centerEntity = (other.boxMin + other.boxMax) * 0.5f;

        // Calculate the direction vector from the player to the entity
        glm::vec3 direction = centerEntity - centerPlayer;


        // Calcul de la pénétration sur chaque axe
        float penX = std::min(boxMax.x - other.boxMin.x, other.boxMax.x - boxMin.x);
        float penY = std::min(boxMax.y - other.boxMin.y, other.boxMax.y - boxMin.y);
        float penZ = std::min(boxMax.z - other.boxMin.z, other.boxMax.z - boxMin.z);

        glm::vec3 res(0.0f);

        // Détermination de l'axe de pénétration le plus faible
        if (penX <= penY && penX <= penZ) {
            // Pénétration sur l'axe X
            res.x = (direction.x > 0) ? -1.0f : 1.0f;
        } else if (penY <= penX && penY <= penZ) {
            // Pénétration sur l'axe Y
            res.y = (direction.y > 0) ? -1.0f : 1.0f;
        } else {
            // Pénétration sur l'axe Z
            res.z = (direction.z > 0) ? -1.0f : 1.0f;
        }

        return res;
    }

};

class Mesh {
public:
    // Mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;
    GLuint VAO;

    // constructor
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    // render the mesh
    void Draw(Shader &shader);

    //get bounding box
    AABB getBoundingBox() const { return boundingBox; }
    void drawCollisionBox(Shader &shader);

private:
    // bounding box of mesh
    AABB boundingBox;

    // render data 
    GLuint VBO, EBO;

    // initializes all the buffer objects/arrays
    void setupMesh();
};