#pragma once

#include <glm/glm.hpp> //glm::mat4
#include <list> //std::list
#include <array> //std::array
#include <memory> //std::unique_ptr
#include <glm/gtc/matrix_transform.hpp> //glm::translate, glm::rotate, glm::scale
#include <GL/glew.h> //GLuint
#include "Model.hpp"
#include "Transform.hpp" //Transform
#include <common/shader.hpp>
#include "Camera.hpp"


class Entity {
public:
	// Hierarchy
	std::list<Entity*> children;
	Entity* parent;

	// Constructors
	Entity(Shader shader) : model(""), shader(shader), parent(nullptr){}
	Entity(std::string filename, Shader shader) : model(filename), shader(shader) ,parent(nullptr) {} // Entity with geometry

	// Geometry
	Model model;

	// Model Matrix
	Transform transform;

	// ID
	GLuint program_scene;

	// Shader
	Shader shader;

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


	void render(Camera &_camera) {
		glUseProgram(program_scene);

        glUniformMatrix4fv(glGetUniformLocation(program_scene, "View"), 1, GL_FALSE, &_camera.getViewMatrix()[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(program_scene, "Projection"), 1, GL_FALSE, & _camera.getProjectionMatrix()[0][0]);
		
		glUniformMatrix4fv(glGetUniformLocation(program_scene, "Model"), 1, GL_FALSE, &transform.getModelMatrix()[0][0]); // Model Matrix
		
		// Draw Mesh
		model.Draw(shader); // Render geometry

		for (auto&& child : children) {
			child->render(_camera);
		}
	}

	void bindVBO(GLuint programID) {
		this->program_scene = programID;
		for (auto&& child : children) {
			child->bindVBO(programID);
		}
	}

	void unbindVBO() {
		for (auto&& child : children) {
			child->unbindVBO();
		}
	}
};