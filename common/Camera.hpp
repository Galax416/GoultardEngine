#pragma once

#include <common/Utils.hpp>

// #define M_PI       3.14159265358979323846f   // pi

class Camera {
public:

    Camera() {
        init();
    };
    void init();
    void update(float _deltaTime, GLFWwindow* _window);
    void updateInput(float _deltaTime, GLFWwindow* _window);
    void computeView(glm::mat4& _outProjectionMatrix, glm::mat4& _outviewMatrix, glm::vec3& _position, glm::quat _rotation, float _fovDegree);
    void setEditionMode(bool _isEditionMode) { m_isEditionMode = _isEditionMode; }

	glm::quat getRotation() const {return m_rotation;}
    glm::vec3 getRotationEuler() const {return m_eulerAngle;}
    glm::vec3 getFront() const {return m_front;}
	glm::mat4 getViewMatrix() const {return m_viewMatrix;}
	glm::mat4 getProjectionMatrix() const {return m_projectionMatrix;}
    glm::vec3 getPosition() const {return m_position;}
    bool getEditionMode() const {return m_isEditionMode;}


    void setFov(float fov) { m_fovDegree = fov; }
    void setPosition(glm::vec3 _position) { m_position = _position; }
    void setRotation(glm::quat _rotation) { m_rotation = _rotation; }
    void setRotation(glm::vec3 _eulerAngle) { m_eulerAngle = _eulerAngle; }
    void setTranslationSpeed(float _speed) { m_translationSpeed = _speed; }

    glm::vec3 simulateIdle();
    glm::vec3 simulateWalking();
    glm::vec3 simulateSprint();


protected:
    // Camera parameters 
    float       m_fovDegree{ 45.0 };
    float       m_translationSpeed{ 2.5f };
	float       m_rotationSpeed{ 0.1f };
    glm::vec3   m_eulerAngle{ glm::vec3(0.0f, 0.0f, 0.0f) };
    glm::vec3   m_position{ glm::vec3(0.0f, 0.0f, 0.0f) };
    glm::vec3   m_front{ glm::vec3(0.0f, 0.0f, 0.0f) };
    glm::quat   m_rotation{};

    // Edition mode
    bool m_isEditionMode{ true };

    // View
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;

};
