#include <glm/glm.hpp> //glm::mat4
#include <glm/gtc/matrix_transform.hpp> //glm::translate, glm::rotate, glm::scale
#include <glm/gtc/quaternion.hpp> //glm::quat
#include <GL/glew.h> //GLuint

class Transform {
protected:
	//Local space information
	glm::vec3 m_pos = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_eulerRot = { 0.0f, 0.0f, 0.0f }; //In degrees
	glm::vec3 m_scale = { 1.0f, 1.0f, 1.0f };

	glm::quat m_rotation; // In quaternion
	bool hasquat = false;

	//Global space information concatenate in matrix
	glm::mat4 m_modelMatrix = glm::mat4(1.0f);

	//Dirty flag
	bool m_isDirty = true;

protected:
	glm::mat4 getLocalModelMatrix() {
		if (hasquat) { // if we have a quaternion, we use it
			glm::mat4 rotationMatrix = glm::mat4_cast(m_rotation);
			return glm::translate(glm::mat4(1.0f), m_pos) * rotationMatrix * glm::scale(glm::mat4(1.0f), m_scale);
		}
		// else we use euler angles
		const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(m_eulerRot.x), glm::vec3(1.0f, 0.0f, 0.0f));
		const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(m_eulerRot.y), glm::vec3(0.0f, 1.0f, 0.0f));
		const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_eulerRot.z), glm::vec3(0.0f, 0.0f, 1.0f));

		// Y * X * Z
		const glm::mat4 rotationMatrix = transformY * transformX * transformZ;

		// translation * rotation * scale (also know as TRS matrix)
		return glm::translate(glm::mat4(1.0f), m_pos) * rotationMatrix * glm::scale(glm::mat4(1.0f), m_scale);
	}
public:

	void computeModelMatrix() {
		m_modelMatrix = getLocalModelMatrix();
		m_isDirty = false;
	}

	void computeModelMatrix(const glm::mat4& parentGlobalModelMatrix) {
		m_modelMatrix = parentGlobalModelMatrix * getLocalModelMatrix();
		m_isDirty = false;
	}

	void setLocalPosition(const glm::vec3& newPosition) {
		m_pos = newPosition;
		m_isDirty = true;
	}

	void translate(const glm::vec3& newPosition) {
		m_pos += newPosition;
		m_isDirty = true;
	}

	void setLocalRotation(const glm::quat& newRotation) {
		m_rotation = newRotation;
		hasquat = true;
		m_isDirty = true;
	}

	void setLocalRotation(const glm::vec3& newRotation) {
		m_eulerRot = newRotation;
		m_isDirty = true;
	}

	void setRotation(const glm::vec3& newRotation) {
		m_eulerRot += newRotation;
		m_isDirty = true;
	}

	void setLocalScale(const glm::vec3& newScale) {
		m_scale = newScale;
		m_isDirty = true;
	}
	const glm::vec3& getLocalPosition() const {
		return m_pos;
	}

	const glm::vec3& getLocalRotation() const {
		return m_eulerRot;
	}

	const glm::quat& getLocalRotationQuat() const {
		return m_rotation;
	}

	const glm::vec3& getLocalScale() const {
		return m_scale;
	}

	const glm::mat4& getModelMatrix() const {
		return m_modelMatrix;
	}

	bool isDirty() const {
		return m_isDirty;
	}
};