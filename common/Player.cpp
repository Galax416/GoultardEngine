#include <common/Player.hpp>

Player::Player(Model *model, Shader *shader, Camera camera) : Entity(model, shader) {
    camera.setEditionMode(false);
    this->camera = camera;
	this->camera.setPosition(glm::vec3(0.f, 90.f, 0.f));
	this->camera.setRotation(glm::quat(glm::vec3(0.f, 0.f, 0.f)));
	this->camera.setEditionMode(false);
}

Player::Player(std::string filename, Shader *shader, Camera camera) : Entity(filename, shader) {
    camera.setEditionMode(false);
    this->camera = camera;
	this->camera.setPosition(glm::vec3(0.f, 90.f, 0.f));
	this->camera.setRotation(glm::quat(glm::vec3(0.f, 0.f, 0.f)));
	this->camera.setEditionMode(false);
}

void Player::jump(float jumpSpeed) {
	if (isGrounded) {
		velocity.y = jumpSpeed;
		isGrounded = false;
	}
}

void Player::updateInput(bool isColliding, float _deltaTime, GLFWwindow* _window) {   
	camera.update(_deltaTime, _window);
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


	// Apply gravity if not grounded
	if (!isGrounded) {
		velocity.y -= gravity * _deltaTime;
	} else {
		velocity.y = 0.0f;
	}

	// sprint
	if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		playerTranslationSpeed = m_translationSpeed * 3 * _deltaTime;
		camera.setFov(55.0f);
		m_isSprinting = true;
		
	} else {
		camera.setFov(45.0f);
		m_isSprinting = false;
	}

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

	// footsteps sound
	if(m_lastValidPosition != pos && isGrounded) {
		if (glfwGetTime() - lastPlayed > 2) {
			m_soundEngine->play2D("../data/sound/footstep.wav", false);
			lastPlayed = glfwGetTime();
		}
	}


	// jump
	if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		jump(5.0f);
		m_jumpKeyPressed = true;
	} else m_jumpKeyPressed = false;

	glm::vec3 cameraRotation = eulerAngle;
	if (m_lastValidPosition == pos) cameraRotation += camera.simulateIdle();
	//else if (m_isSprinting) cameraRotation += camera.simulateSprint();
	else if(isGrounded) cameraRotation += camera.simulateWalking();

	
	updatePlayer(isColliding, pos + velocity, cameraRotation);

	// Weapon
	if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) { 
		weapon->shoot(camera.getPosition(), camera.getFront(), camera.getRotationEuler(), bulletOffset, 3000.0f, 5.0f);
	}
	if(glfwGetKey(_window, GLFW_KEY_R) == GLFW_PRESS) {
		weapon->reload();
	}

}

void Player::updatePlayer(bool isColliding, glm::vec3 pos, glm::vec3 eulerAngle) {
	
	// check if the player is out of the map
	if (transform.getLocalPosition().y < -8000.0f) {
		transform.setLocalPosition(glm::vec3(0.0f, 400.0f, 0.0f));
		return;
	}

	glm::vec3 cameraSprintPos = camera.getFront() * 15.0f;


	// Compute the camera position
    glm::quat rotationQuat = glm::angleAxis(glm::radians(eulerAngle.y), VEC_UP); // rotate around the Y axis
    glm::vec3 rotatedOffset;
	if (m_isSprinting) rotatedOffset = rotationQuat * cameraOffset + cameraSprintPos;
	else rotatedOffset = rotationQuat * cameraOffset;

	// Update the camera position and rotation
    camera.setRotation(eulerAngle);
	transform.setLocalRotation(glm::vec3(0.0f, eulerAngle.y, 0.0f));


	if (isColliding) {
		if (m_normalCollision.y < 0) {
			glm::vec3 groundPos = glm::vec3(pos.x, m_jumpKeyPressed ? pos.y : m_heightGround, pos.z);

			transform.setLocalPosition(groundPos);
			camera.setPosition(groundPos + rotatedOffset);
		} 
		if (m_normalCollision.x != 0 || m_normalCollision.z != 0) {

			camera.setPosition(m_lastValidPosition - m_normalCollision +  rotatedOffset);
			transform.setLocalPosition(m_lastValidPosition - m_normalCollision);
		}
		
		isGrounded = true;

	} else {
		camera.setPosition(pos + rotatedOffset);
		transform.setLocalPosition(pos);
		m_normalCollision = glm::vec3(0.0f);
		isGrounded = false;
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

	bool collisionDetected = false;

	// And check collision with other child
	for (auto&& child : other.children) {
		if (CheckCollisionWithEntity(*child))
			collisionDetected = true;
	}

	return collisionDetected;
}

bool Player::CheckCollisionWithSingleEntity(Entity &entity) { // AABB - AABB Collision
	AABB playerAABB = this->model->getBoundingBox();
	if (entity.model == nullptr) return false;
	AABB entityAABB = entity.model->getBoundingBox();

	if (entityAABB.boxMax == glm::vec3(-std::numeric_limits<float>::infinity()) || entityAABB.boxMin == glm::vec3(std::numeric_limits<float>::infinity())) return false;

	// Update bounding box
	for (auto&& child : this->children) {
		AABB chidlAABB = child->model->getBoundingBox();
		chidlAABB.updateBoundingBox(child->transform.getModelMatrix());
		playerAABB.updateBoundingBox(this->transform.getModelMatrix());
		playerAABB.expand(chidlAABB);
	}
	entityAABB.updateBoundingBox(entity.transform.getModelMatrix());


	if (playerAABB.intersects(entityAABB)) { // Collision detected
		glm::vec3 n = playerAABB.getNormalCollision(entityAABB);
		m_normalCollision.x += (std::abs(n.x) == 1) ? -n.x : 0.0f;
		m_normalCollision.y += (std::abs(n.y) == 1) ? -n.y : 0.0f;
		m_normalCollision.z += (std::abs(n.z) == 1) ? -n.z : 0.0f;

		m_normalCollision *= 0.2f;
		
		m_heightGround = entityAABB.boxMax.y;
		return true;
	
	} else // No collision detected
		return false;
}

void Player::respawn(glm::vec3 pos) {
	m_soundEngine->play2D("../data/sound/dspldeth.wav", false);
	transform.setLocalPosition(pos);
	setHealth(100);
	weapon->setAmmo(weapon->getMaxAmmo());
}
