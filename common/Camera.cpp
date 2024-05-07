#include <common/Camera.hpp>

void Camera::init()
{
    m_fovDegree = 45.0f;
    m_translationSpeed = 50.0f;
	m_rotationSpeed = 2.5f;
    m_position = glm::vec3(0.f, 0.f, 0.f);
	m_eulerAngle = glm::vec3(0.f, 0.f, 0.f);
	m_rotation = glm::quat{};
	m_front = glm::normalize(glm::vec3(glm::toMat4(m_rotation)[2]));

    m_isEditionMode = true;
}

void Camera::computeView(glm::mat4& _outProjectionMatrix, glm::mat4& _outviewMatrix, glm::vec3& _position, glm::quat _rotation, float _fovDegree)
{
	// Projection matrix : FOV, 4:3 ratio, display range : 0.1 unit <-> 100 units
	_outProjectionMatrix = glm::perspective(glm::radians(_fovDegree), 16.0f / 9.0f, 0.1f, 20000.0f);

	const glm::vec3 front = normalize(_rotation* VEC_FRONT);
	const glm::vec3 up = normalize(_rotation * VEC_UP);

	// Camera matrix
	_outviewMatrix = glm::lookAt(_position, _position + front, up);
}

float Camera::clipAngle180(float angle)
{
    return std::fmod(angle + 180.0f, 360.0f) - 180.0f;
}

glm::vec3 Camera::quatToEuler(glm::quat _quat)
{
	// Opengl quat to euler function give yaw betweel -90 and 90
	// If you want correct pitch and yaw you can use this 
	// Src http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
	// But roll will be bewteen -90 and 90 here

	glm::vec3 eulerAngles;

	float test = _quat.x * _quat.y + _quat.z * _quat.w;

	if (test > 0.499f) { // singularity at north pole
		eulerAngles.y = 2.f * atan2(_quat.x, _quat.w);
		eulerAngles.z = M_PI / 2.f;
		eulerAngles.x = 0.f;
		return eulerAngles;
	}
	if (test < -0.499f) { // singularity at south pole
		eulerAngles.y = -2.f * atan2(_quat.x, _quat.w);
		eulerAngles.z = -M_PI / 2.f;
		eulerAngles.x = 0.f;
		return eulerAngles;
	}
	float sqx = _quat.x * _quat.x;
	float sqy = _quat.y * _quat.y;
	float sqz = _quat.z * _quat.z;


	eulerAngles.y = atan2(2.f * _quat.y * _quat.w - 2.f * _quat.x * _quat.z, 1.f - 2.f * sqy - 2.f * sqz);
	eulerAngles.z = asin(2.f * test);
	eulerAngles.x = atan2(2.f * _quat.x * _quat.w - 2.f * _quat.y * _quat.z, 1.f - 2.f * sqx - 2.f * sqz);

	return eulerAngles;
}

glm::vec3 Camera::projectVectorOnPlan(glm::vec3 vector, glm::vec3 normalPlan) 
{
	return glm::cross(normalPlan, glm::cross(vector, normalPlan));
}

float Camera::interpolate(float ratio, InterpolationType type)
{
	switch (type) {
        case SMOOTHSTEP:
            return ratio * ratio * (3 - 2 * ratio); // Interpolation smooth
        case COSINUS:
            return 0.5f * (1.0f - cos(ratio * M_PI));
        case EXPONENTIAL:
            return exp(ratio) / exp(1.0f); // Interpolation exponentielle
        case LOGARITHMIC:
            return log(ratio * (glm::e<float>() - 1.0f) + 1.0f) / log(glm::e<float>()); // Interpolation logarithmique
        default:
            return ratio; // Interpolation linéaire, pas de modification
    }
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