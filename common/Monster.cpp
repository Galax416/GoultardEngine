#include <common/Monster.hpp>

Monster::Monster(std::string filename, Shader *shader) : Entity(filename, shader) {
}

void Monster::updateMonster(bool isColliding, glm::vec3 pos, glm::vec3 eulerAngle, float deltaTime) {
    if (isColliding) {
        transform.setLocalPosition(m_lastValidPosition);
    } else {
        transform.setLocalPosition(pos);
    }
    transform.setLocalRotation(eulerAngle);
}

void Monster::detectPlayer(glm::vec3 playerPos, float deltaTime) {
    playerPos.y += 83.0f; // ennemy aim at the head of the player
    glm::vec3 monsterPos = transform.getLocalPosition();
    float distance = glm::distance(monsterPos, playerPos);
    if (distance < m_detectionRange) {
		if (distance > 5.0f) { // prevent naughty things
			// Move towards the player
			glm::vec3 direction = glm::normalize(playerPos - monsterPos);
			transform.setLocalPosition(monsterPos + direction * m_translationSpeed * deltaTime);

			// look at the player
			glm::quat rotation = glm::quatLookAt(direction, VEC_UP);
			glm::quat initialRotation = glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			rotation = rotation * initialRotation; // rotate the model
			rotation = glm::normalize(rotation);

			transform.setLocalRotation(rotation);
		}
        if (distance < 50.0f) {
            // Attack the player
            std::cout << "Attack the player" << std::endl;
        }
    }
}

// Same as Player
bool Monster::CheckCollisionWithEntity(Entity &other) {
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

bool Monster::CheckCollisionWithSingleEntity(Entity &entity) { // AABB - AABB Collision
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