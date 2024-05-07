#include <common/Player.hpp>

Player::Player(std::string filename, Shader *shader, Camera camera) : Entity(filename, shader), weapon(shader) {
    camera.setEditionMode(false);
    this->camera = camera;
	this->camera.init();
	this->camera.setPosition(glm::vec3(0.f, 90.f, 0.f));
	this->camera.setRotation(glm::quat(glm::vec3(0.f, 0.f, 0.f)));
	this->camera.setEditionMode(false);
}

void Player::updateInput(bool isColliding, float _deltaTime, GLFWwindow* _window) {   
	float playerTranslationSpeed = m_translationSpeed * _deltaTime;
	float playerRotationSpeed = m_rotationSpeed * _deltaTime;

	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Get the mouse position
	double mouseX, mouseY;
	glfwGetCursorPos(_window, &mouseX, &mouseY);

	// Compute the mouse movement
	static double lastMouseX = mouseX;
	static double lastMouseY = mouseY;
	double deltaX = mouseX - lastMouseX;
	double deltaY = mouseY - lastMouseY;
	lastMouseX = mouseX;
	lastMouseY = mouseY;

	// Compute the new rotation angles
	glm::vec3 eulerAngle = camera.getRotationEuler();

	eulerAngle.y -= (float)(deltaX) * m_rotationSpeed;
	eulerAngle.y = Camera::clipAngle180(eulerAngle.y); // Clamp the yaw angle between -180 and 180 degrees
	eulerAngle.x += (float)(deltaY) * m_rotationSpeed;
	eulerAngle.x = glm::clamp(eulerAngle.x, -89.9f, 89.9f); // Clamp the pitch angle between -90 and 90 degrees


	// ZQSD movement
	glm::vec3 pos = transform.getLocalPosition();
	this->m_lastValidPosition = pos;
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
		pos += glm::normalize(Camera::projectVectorOnPlan(camera.getFront(), VEC_UP)) * playerTranslationSpeed;
	}
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
		pos -= glm::normalize(Camera::projectVectorOnPlan(camera.getFront(), VEC_UP)) * playerTranslationSpeed;
	}
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
		pos -= glm::normalize(Camera::projectVectorOnPlan(glm::normalize(glm::cross(camera.getFront(), VEC_UP)), VEC_UP)) * playerTranslationSpeed;
	}
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
		pos += glm::normalize(Camera::projectVectorOnPlan(glm::normalize(glm::cross(camera.getFront(), VEC_UP)), VEC_UP)) * playerTranslationSpeed;
	}

	updatePlayer(isColliding, pos, eulerAngle);

	// Weapon
	if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS) {
		weapon.shoot(weapon.transform.getLocalPosition(), camera.getFront(), 20.0f, 2.0f);
	}
	if(glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS) {
		weapon.reload();
	}

}

void Player::updatePlayer(bool isColliding, glm::vec3 pos, glm::vec3 eulerAngle) {

	// Compute the camera position
    glm::vec3 cameraOffset(0.f, 83.f, 15.f); // offset from the player position
    glm::quat rotationQuat = glm::angleAxis(glm::radians(eulerAngle.y), glm::vec3(0.0f, 1.0f, 0.0f)); // rotate around the Y axis
    glm::vec3 rotatedOffset = rotationQuat * cameraOffset;
    glm::vec3 finalCameraPosition = pos + rotatedOffset;

	// Update the camera position and rotation
    camera.setRotation(eulerAngle);
	transform.setLocalRotation(glm::vec3(0.0f, eulerAngle.y, 0.0f));
	
	std::cout << isColliding << std::endl;
	if (isColliding) {
		transform.setLocalPosition(m_lastValidPosition - m_normalCollision);
		camera.setPosition(m_lastValidPosition - m_normalCollision +  rotatedOffset);

	}
	else {
		transform.setLocalPosition(pos);
		camera.setPosition(pos + rotatedOffset);

	}

	glm::vec3 weaponOffset(-20.0f, 70.0f, 60.0f); // offset from the player position
	for (auto&& child : children) {
		// Send X & Z axis for the child
		child->transform.setLocalPosition(weaponOffset);
		child->transform.setLocalRotation(glm::vec3(eulerAngle.x - 90.0f, 0.0f, eulerAngle.z));
	}
}

bool Player::CheckCollisionWithEntity(Entity &other) {
	// Check collision with other
	if (CheckCollisionWithSingleEntity(other))
		return true;

	// And check collision with other child
	for (auto&& child : other.children) {
		if (CheckCollisionWithEntity(*child))
			return true;
	}

	return false;
}

bool Player::CheckCollisionWithSingleEntity(Entity &entity) { // AABB - AABB Collision
	AABB playerAABB = this->model.getBoundingBox();
	for (auto&& child : this->children) {
		playerAABB.expand(child->model.getBoundingBox());
	}
	AABB entityAABB = entity.model.getBoundingBox();
	if (entityAABB.boxMax == glm::vec3(-std::numeric_limits<float>::infinity()) || entityAABB.boxMin == glm::vec3(std::numeric_limits<float>::infinity())) return false;

	// Update bounding box
	playerAABB.updateBoundingBox(this->transform.getModelMatrix());
	entityAABB.updateBoundingBox(entity.transform.getModelMatrix());


	if (playerAABB.intersects(entityAABB)) {
		// Collision detected
		m_normalCollision = - playerAABB.getNormalCollision(entityAABB) * 0.1f;
		return true;
	}
	// No collision detected
	return false;
}


void Player::initHUD(GLuint shaderID) {
	initText2D("../data/font/Holstein.tga", shaderID);
}

void Player::DrawHUD() {
	// Print the health
	char text[256];
	sprintf(text, "Health: %d", m_health);
	printText2D(text, 100, 500, 60);
}