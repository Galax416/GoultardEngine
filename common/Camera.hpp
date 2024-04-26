#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

// #define M_PI       3.14159265358979323846f   // pi

enum InterpolationType {
    SMOOTHSTEP,
    COSINUS,
    EXPONENTIAL,
    LOGARITHMIC
};

static glm::vec3 VEC_ZERO{ 0.f,0.f,0.f };
static glm::vec3 VEC_UP{ 0.f,1.f,0.f };
static glm::vec3 VEC_FRONT{ 0.f,0.f,-1.f };
static glm::vec3 VEC_RIGHT{ 1.f,0.f,0.f };

class Camera {
public:

    void init();
    void update(float _deltaTime, GLFWwindow* _window);
    void updateInput(float _deltaTime, GLFWwindow* _window);
    void computeView(glm::mat4& _outProjectionMatrix, glm::mat4& _outviewMatrix, glm::vec3& _position, glm::quat _rotation, float _fovDegree);
    void setEditionMode(bool _isEditionMode) { m_isEditionMode = _isEditionMode; }

	glm::quat getRotation() const {return m_rotation;}
	glm::mat4 getViewMatrix() const {return m_viewMatrix;}
	glm::mat4 getProjectionMatrix() const {return m_projectionMatrix;}


private:

    // Utils
    glm::vec3 projectVectorOnPlan(glm::vec3 vector, glm::vec3 normalPlan);
    float clipAngle180(float angle);
    float interpolate(float ratio, InterpolationType type);
    glm::vec3 quatToEuler(glm::quat _quat);

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
