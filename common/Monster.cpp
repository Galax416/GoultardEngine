#include <common/Monster.hpp>

Monster::Monster(std::string filename, Shader *shader) : Entity(filename, shader) {}

Monster::Monster(Model *model, Shader *shader) : Entity(model, shader) {}

void Monster::updateMonster(bool isColliding, glm::vec3 pos, glm::vec3 eulerAngle, float deltaTime) {
    if (isColliding) {
        transform.setLocalPosition(m_lastValidPosition);
    } else {
        transform.setLocalPosition(pos);
    }
    transform.setLocalRotation(eulerAngle);
}

void Monster::detectPlayer(glm::vec3 playerPos, float deltaTime, float &playerHealth) {
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
			transform.setLocalPosition(monsterPos + direction * m_translationSpeed * deltaTime);

			// look at the player
			glm::quat rotation = glm::quatLookAt(direction, VEC_UP);
			glm::quat initialRotation = glm::angleAxis(glm::radians(RotationOffset), glm::vec3(0.0f, 1.0f, 0.0f)); // depending on the model
			rotation = rotation * initialRotation; // rotate the model
			rotation = glm::normalize(rotation);

			transform.setLocalRotation(rotation);
		}
        if (distance < 50.0f) {
            // Attack the player
            m_soundEngine->play2D("../data/sound/monster/dssgtatk.wav", false);
            static float attackTimer = 0.0f;
            attackTimer += deltaTime;
            if (attackTimer >= attackSpeed) {
                playerHealth -= damage;
                attackTimer = 0.0f;
            }
        }
    }
}

void Monster::respawn(glm::vec3 pos) {
    m_soundEngine->play2D("../data/sound/monster/dskntdth.wav", false);
    transform.setLocalPosition(pos);
    m_health = 100;
    isChasing = false;
}