#include <common/Player.hpp>

Player::Player(std::string filename, Shader shader, Camera camera) : Entity(filename, shader) {
    camera.setEditionMode(false);
    this->camera = camera;
	this->camera.init();
	this->camera.setPosition(glm::vec3(0.f, 90.f, 0.f));
	this->camera.setRotation(glm::quat(glm::vec3(0.f, 0.f, 0.f)));
}

void Player::updateInput(float _deltaTime, GLFWwindow* _window) {   
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

	glm::vec3 eulerAngle = camera.getRotationEuler();
	if (isMouseLeftPressed) {
		// Modification des angles de rotation de la caméra en fonction du mouvement de la souris
		eulerAngle.y -= (float)(deltaX) * m_rotationSpeed;
		eulerAngle.y = Camera::clipAngle180(eulerAngle.y); // Limite l'angle de yaw entre -180 et 180 degrés
		eulerAngle.x += (float)(deltaY) * m_rotationSpeed;
		eulerAngle.x = glm::clamp(eulerAngle.x, -90.0f, 90.0f); // Limite l'angle de pitch entre -90 et 90 degrés
	}


	// ZQSD
	glm::vec3 pos = transform.getLocalPosition();
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
		pos += camera.getFront() * cameraTranslationSpeed;
	}
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
		pos -= camera.getFront() * cameraTranslationSpeed;
	}
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
		pos -= glm::normalize(glm::cross(camera.getFront(), VEC_UP)) * cameraTranslationSpeed;
	}
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
		pos += glm::normalize(glm::cross(camera.getFront(), VEC_UP)) * cameraTranslationSpeed;
	}

	updatePlayer(pos, eulerAngle);
	
}

void Player::updatePlayer(glm::vec3 pos, glm::vec3 eulerAngle) {


    glm::vec3 cameraOffset(0.f, 83.f, 15.f); // offset from the player position
    glm::quat rotationQuat = glm::angleAxis(glm::radians(eulerAngle.y), glm::vec3(0.0f, 1.0f, 0.0f)); // rotate around the Y axis
    glm::vec3 rotatedOffset = rotationQuat * cameraOffset;
    glm::vec3 finalCameraPosition = pos + rotatedOffset;

	// Update the camera position and rotation
    camera.setPosition(finalCameraPosition);
    camera.setRotation(eulerAngle);

	// Update the player position and rotation
	transform.setLocalRotation(glm::vec3(0.0f, eulerAngle.y, 0.0f));
	transform.setLocalPosition(pos);

}
