#include <common/Player.hpp>

Player::Player(std::string filename, Shader *shader, Camera camera) : Entity(filename, shader) {
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

	eulerAngle.y -= (float)(deltaX) * playerRotationSpeed;
	eulerAngle.y = Camera::clipAngle180(eulerAngle.y); // Clamp the yaw angle between -180 and 180 degrees
	eulerAngle.x += (float)(deltaY) * playerRotationSpeed;
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

	updatePlayer(isColliding, pos + velocity, eulerAngle);

	// Weapon
	if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) { 
		glm::vec3 position = transform.getLocalPosition() + weapon->transform.getLocalPosition(); // weapon position
		weapon->shoot(camera.getPosition(), camera.getFront(), camera.getRotationEuler(), bulletOffset, 3000.0f, 5.0f);
	}
	if(glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS) {
		weapon->reload();
	}

}

void Player::updatePlayer(bool isColliding, glm::vec3 pos, glm::vec3 eulerAngle) {
	
	// check if the player is out of the map
	if (transform.getLocalPosition().y < -800.0f) {
		transform.setLocalPosition(glm::vec3(0.0f, 400.0f, 0.0f));
		return;
	}

	// Compute the camera position
    glm::quat rotationQuat = glm::angleAxis(glm::radians(eulerAngle.y), VEC_UP); // rotate around the Y axis
    glm::vec3 rotatedOffset = rotationQuat * cameraOffset;
    glm::vec3 finalCameraPosition = pos + rotatedOffset;

	// Update the camera position and rotation
    camera.setRotation(eulerAngle);
	transform.setLocalRotation(glm::vec3(0.0f, eulerAngle.y, 0.0f));
	
	if (isColliding) {
		transform.setLocalPosition(m_lastValidPosition - m_normalCollision);
		camera.setPosition(m_lastValidPosition - m_normalCollision +  rotatedOffset);

	}
	else {
		transform.setLocalPosition(pos);
		camera.setPosition(pos + rotatedOffset);

	}

	for (auto&& child : children) {
		// Rotate weapon around both X and Y axes
        child->transform.setLocalRotation(glm::vec3(eulerAngle.x - 90.0f, 0.0f, eulerAngle.z));
		// Set the weapon position
        child->transform.setLocalPosition(weaponOffset);

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
	AABB entityAABB = entity.model.getBoundingBox();
	if (entityAABB.boxMax == glm::vec3(-std::numeric_limits<float>::infinity()) || entityAABB.boxMin == glm::vec3(std::numeric_limits<float>::infinity())) return false;

	// Update bounding box
	for (auto&& child : this->children) {
		AABB chidlAABB = child->model.getBoundingBox();
		chidlAABB.updateBoundingBox(child->transform.getModelMatrix());
		playerAABB.updateBoundingBox(this->transform.getModelMatrix());
		playerAABB.expand(chidlAABB);
	}
	entityAABB.updateBoundingBox(entity.transform.getModelMatrix());


	if (playerAABB.intersects(entityAABB)) {
		// Collision detected
		m_normalCollision = - playerAABB.getNormalCollision(entityAABB) * 0.1f;
		return true;
	}
	// No collision detected
	return false;
}

void Player::respawn(glm::vec3 pos) {
	transform.setLocalPosition(pos);
	setHealth(100);
	weapon->setAmmo(weapon->getMaxAmmo());
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