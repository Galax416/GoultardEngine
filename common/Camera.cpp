#include <common/Camera.hpp>

void Camera::init()
{
    m_fovDegree = 45.0f;
    m_translationSpeed = 150.0f;
	m_rotationSpeed = 3.0f;
    m_position = glm::vec3(0.f, 0.f, 0.f);
	m_eulerAngle = glm::vec3(0.f, 0.f, 0.f);
	m_rotation = glm::quat{};
	m_front = glm::normalize(glm::vec3(glm::toMat4(m_rotation)[2]));

    m_isEditionMode = true;
}

void Camera::computeView(glm::mat4& _outProjectionMatrix, glm::mat4& _outviewMatrix, glm::vec3& _position, glm::quat _rotation, float _fovDegree)
{
	// Projection matrix : FOV, 4:3 ratio, display range : 0.1 unit <-> 100 units
	_outProjectionMatrix = glm::perspective(glm::radians(_fovDegree), 16.0f / 9.0f, 0.1f, 10000000.0f);

	const glm::vec3 front = normalize(_rotation* VEC_FRONT);
	const glm::vec3 up = normalize(_rotation * VEC_UP);

	// Camera matrix
	_outviewMatrix = glm::lookAt(_position, _position + front, up);
}

void Camera::updateInput(float _deltaTime, GLFWwindow* _window) {   
	if (m_isEditionMode) {
		float cameraTranslationSpeed = m_translationSpeed * _deltaTime;
		float cameraRotationSpeed = m_rotationSpeed * _deltaTime;

		// Vérifie si le bouton gauche de la souris est enfoncé
		bool isMouseLeftPressed = glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

		// Active ou désactive le mode de capture de la souris en fonction du clic gauche
		glfwSetInputMode(_window, GLFW_CURSOR, isMouseLeftPressed ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);


		// Capture les mouvements de la souris
		double mouseX, mouseY;
		glfwGetCursorPos(_window, &mouseX, &mouseY);

		// Calculez la différence de position de la souris depuis la dernière frame
		static double lastMouseX = mouseX;
		static double lastMouseY = mouseY;
		double deltaX = mouseX - lastMouseX;
		double deltaY = mouseY - lastMouseY;
		lastMouseX = mouseX;
		lastMouseY = mouseY;

		if (isMouseLeftPressed) {
			// Modification des angles de rotation de la caméra en fonction du mouvement de la souris
			m_eulerAngle.y -= (float)(deltaX) * cameraRotationSpeed;
			m_eulerAngle.y = clipAngle180(m_eulerAngle.y); // Limite l'angle de yaw entre -180 et 180 degrés
			m_eulerAngle.x += (float)(deltaY) * cameraRotationSpeed;
			m_eulerAngle.x = glm::clamp(m_eulerAngle.x, -90.0f, 90.0f); // Limite l'angle de pitch entre -90 et 90 degrés
		}


		// ZQSD
		if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
			m_position += m_front * cameraTranslationSpeed;
		}
		if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
			m_position -= m_front * cameraTranslationSpeed;
		}
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
			m_position -= glm::normalize(glm::cross(m_front, VEC_UP)) * cameraTranslationSpeed;
		}
		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
			m_position += glm::normalize(glm::cross(m_front, VEC_UP)) * cameraTranslationSpeed;
		}

		// !!!!!!!!!!!!!!!!! A revoir en dessous !!!!!!!!!!!!!!!!!!

		// Modification de la hauteur de la caméra avec les touches A et E
		if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			m_position.y += cameraTranslationSpeed;
		}
		if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			m_position.y -= cameraTranslationSpeed;
		}
	}

}

void Camera::update(float _deltaTime, GLFWwindow* _window) {

    if(m_isEditionMode) updateInput(_deltaTime, _window);

    // Update la rotation
	m_rotation = glm::quat(glm::radians(m_eulerAngle));

	// Recalcule du vecteur front
	m_front = glm::vec3(glm::toMat4(m_rotation)[2]);

	// Normaliser le vecteur m_front
	m_front = glm::normalize(m_front);

    computeView(m_projectionMatrix, m_viewMatrix, m_position, m_rotation, m_fovDegree);
	
}

glm::vec3 Camera::simulateIdle() {
	float time = glfwGetTime();
    float rotationOffsetYaw = 0.01f * glm::sin(time * 1.0f);
    float rotationOffsetPitch = 0.01f * glm::cos(time * 2.0f);

    return glm::vec3(rotationOffsetPitch, rotationOffsetYaw, 0.0f);
}

glm::vec3 Camera::simulateWalking() {
	float time = glfwGetTime();
    float rotationOffsetYaw = 0.05 * glm::sin(time * 5.0f);
    float rotationOffsetPitch = 0.02 * glm::cos(time * 2.0f);

    return glm::vec3(rotationOffsetPitch, rotationOffsetYaw, 0.0f);
}

glm::vec3 Camera::simulateSprint() {
	float time = glfwGetTime();
    float rotationOffsetYaw = 0.8 * glm::sin(time * 20.0f);
    float rotationOffsetPitch = 0.05 * glm::cos(time * 20.0f);

    return glm::vec3(rotationOffsetPitch, rotationOffsetYaw, 0.0f);
}