#include <common/Monster.hpp>


Monster::Monster(std::string filename, Shader *shader) : Entity(filename, shader) {}

Monster::Monster(Model *model, Shader *shader) : Entity(model, shader) {}

void Monster::updateMonster(bool isColliding, glm::vec3 pos, glm::quat eulerAngle) {
    if (isColliding && isGravityEntity) {
		if (m_normalCollision.y < 0) {
			transform.setLocalPosition(glm::vec3(pos.x, m_heightGround-5, pos.z));
		} 
		if (m_normalCollision.x != 0 || m_normalCollision.z != 0) {
			transform.setLocalPosition(m_lastValidPosition - m_normalCollision);
		}
		m_normalCollision.y = 0;
        
		isGrounded = true;

	} else {
		transform.setLocalPosition(pos);
		m_normalCollision = glm::vec3(0.0f);
		isGrounded = false;
	}

    transform.setLocalRotation(eulerAngle);
}

std::pair<glm::vec3, glm::quat> Monster::detectPlayer(glm::vec3 playerPos, float deltaTime, float &playerHealth) {
    playerPos.y += 83.0f; // ennemy aim at the head of the player
    glm::vec3 monsterPos = transform.getLocalPosition();
    float distance = glm::distance(monsterPos, playerPos);
    if (distance < m_detectionRange || isChasing) {
        if (!isChasing) {
            m_soundEngine->play2D("../data/sound/monster/dssgtsit.wav", false);
            isChasing = true;
        }
		if (distance > 5.0f) { // prevent naughty things
			// Move towards the player
			glm::vec3 direction = glm::normalize(playerPos - monsterPos);
			// transform.setLocalPosition(monsterPos + direction * m_translationSpeed * deltaTime);
            glm::vec3 pos = monsterPos + direction * m_translationSpeed * deltaTime;

			// look at the player
            glm::quat rotation = glm::quatLookAt(direction, VEC_UP);
            if (isGravityEntity) rotation = extractYaw(rotation);
			glm::quat initialRotation = glm::angleAxis(glm::radians(RotationOffset), glm::vec3(0.0f, 1.0f, 0.0f)); // depending on the model
			rotation = rotation * initialRotation; // rotate the model
			rotation = glm::normalize(rotation);

			transform.setLocalRotation(rotation);
		}
        if (distance < 50.0f) {
            // Attack the player
            if (!m_soundEngine->isCurrentlyPlaying("../data/sound/monster/dssgtatk.wav")) m_soundEngine->play2D("../data/sound/monster/dssgtatk.wav", false);
            static float attackTimer = 0.0f;
            attackTimer += deltaTime;
            if (attackTimer >= attackSpeed) {
                playerHealth -= damage;
                attackTimer = 0.0f;
            }

            return std::make_pair(pos, rotation);
		}
        
    }

    return std::make_pair(monsterPos, transform.getLocalRotationQuat());
}

void Monster::update(bool isColliding, float deltaTime, glm::vec3 playerPos, float &playerHealth) {
    // Apply gravity if not grounded and if is a gravity entity
	if (!isGrounded && isGravityEntity) {
		velocity.y -= gravity * deltaTime;
	} else {
		velocity.y = 0.0f;
	}

    m_lastValidPosition = transform.getLocalPosition();
    std::pair<glm::vec3, glm::quat> movement = detectPlayer(playerPos, deltaTime, playerHealth);
    updateMonster(isColliding, movement.first + velocity, movement.second);

}

bool Monster::CheckCollisionWithEntity(Entity &other) {
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

bool Monster::CheckCollisionWithSingleEntity(Entity &entity) { // AABB - AABB Collision
	AABB monsterAABB = this->model->getBoundingBox();
	if (entity.model == nullptr) return false;
	AABB entityAABB = entity.model->getBoundingBox();

	if (monsterAABB.boxMax == glm::vec3(-std::numeric_limits<float>::infinity()) || monsterAABB.boxMin == glm::vec3(std::numeric_limits<float>::infinity())) return false;
	if (entityAABB.boxMax == glm::vec3(-std::numeric_limits<float>::infinity()) || entityAABB.boxMin == glm::vec3(std::numeric_limits<float>::infinity())) return false;


    monsterAABB.updateBoundingBox(this->transform.getModelMatrix());
	entityAABB.updateBoundingBox(entity.transform.getModelMatrix());


	if (monsterAABB.intersects(entityAABB)) { // Collision detected
		glm::vec3 n = monsterAABB.getNormalCollision(entityAABB);
		m_normalCollision.x += (std::abs(n.x) == 1) ? -n.x : 0.0f;
		m_normalCollision.y += (std::abs(n.y) == 1) ? -n.y : 0.0f;
		m_normalCollision.z += (std::abs(n.z) == 1) ? -n.z : 0.0f;

		// m_normalCollision *= 1.0f;
		
		m_heightGround = entityAABB.boxMax.y;
		return true;
	
	} else // No collision detected
		return false;
}

void Monster::respawn(glm::vec3 pos) {
    m_soundEngine->play2D("../data/sound/monster/dskntdth.wav", false);
    transform.setLocalPosition(pos);
    m_health = m_maxHealth;
    isChasing = false;
}