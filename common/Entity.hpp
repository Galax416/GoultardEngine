#include <glm/glm.hpp> //glm::mat4
#include <list> //std::list
#include <array> //std::array
#include <memory> //std::unique_ptr
#include <glm/gtc/matrix_transform.hpp> //glm::translate, glm::rotate, glm::scale
#include <GL/glew.h> //GLuint
#include  "Mesh.hpp" //Mesh
#include "Transform.hpp" //Transform


class Entity {
public:
	// Hierarchy
	std::list<Entity*> children;
	Entity* parent;

	// Constructors
	Entity() : parent(nullptr){}
	Entity(std::string filename) : mesh(filename), parent(nullptr) {} // Entity with geometry
	Entity(std::vector<unsigned short>& indices, std::vector<glm::vec3>& indexed_vertices, std::vector<glm::vec2>& indexed_uvs) 
	: mesh(indices, indexed_vertices, indexed_uvs), parent(nullptr) {} // Entity with geometry

	// Geometry
	Mesh mesh;

	// Model Matrix
	Transform transform;

	// ID
	GLuint modelLocation;

	void addChild(Entity& child) {
		child.parent = this;
		children.push_back(&child);
	}

	// Update entity with dirty's flag
	void updateSelfAndChild() {
		if (transform.isDirty()) {
			forceUpdateSelfAndChild();
			return;
		}
		for (auto&& child : children) {
			child->updateSelfAndChild();
		}
	}

	// Update all entity
	void forceUpdateSelfAndChild() {
		if (parent)
			transform.computeModelMatrix(parent->transform.getModelMatrix());
		else
			transform.computeModelMatrix();

		for (auto&& child : children) {
			child->forceUpdateSelfAndChild();
		}
	}

	void render() {
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &transform.getModelMatrix()[0][0]); // Model Matrix
		mesh.render(); // Render geometry
		for (auto&& child : children) {
			child->render();
		}
	}

	void bindVBO(GLuint programID) {
		mesh.bindVBO(programID);
		this->modelLocation = glGetUniformLocation(programID, "Model");
		for (auto&& child : children) {
			child->bindVBO(programID);
		}
	}

	void unbindVBO() {
		mesh.unbindVBO();
		for (auto&& child : children) {
			child->unbindVBO();
		}
	}
};