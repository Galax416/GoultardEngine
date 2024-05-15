#pragma once

#include <common/Entity.hpp>
#include <common/Weapon.hpp>
#include <common/Utils.hpp>
#include <common/text2D.hpp>


class Monster : public Entity {

private:
    float m_translationSpeed{ 300.0f };
    float m_rotationSpeed{ 2.5f };
    float m_health{ 100 };
    float m_maxHealth{ 100 };
    float m_detectionRange{ 1400.0f };

    float damage{ 20.0f };
    float attackSpeed{ 0.5f };

    float RotationOffset{ 0.0f };

    bool isChasing{ false }; // in Aggro mode (ex : player hit the monster)

    float m_heightGround{ 0.0f };

    glm::vec3 m_lastValidPosition;
    glm::vec3 m_normalCollision;
    glm::vec3 spawnPoint;

public:
    Monster(std::string filename, Shader *shader);
    Monster(Model *model, Shader *shader);

    void updateMonster(bool isColliding=false, glm::vec3 pos=glm::vec3(0.0f), glm::quat eulerAngle= glm::quat());
    void update(bool isColliding, float deltaTime, glm::vec3 slayerPos, float &slayerHealth);


    void respawn(glm::vec3 pos);

    std::pair<glm::vec3, glm::quat> detectPlayer(glm::vec3 playerPos, float deltaTime, float &playerHealth);

    bool CheckCollisionWithEntity(Entity &entity);
    bool CheckCollisionWithSingleEntity(Entity &entity);

    void setHealth(int health) { this->m_health = health;};
    int getHealth() const { return m_health;} ;

    void setMaxHealth(int health) { this->m_maxHealth = health; if(m_health > m_maxHealth) m_maxHealth = m_health;};
    int getMaxHealth() const { return m_maxHealth;} ;

    void setisChasing(bool aggr) { isChasing = aggr; }
    bool getisChasing() const { return isChasing; }

    void setDetectionRange(float range) { m_detectionRange = range; }
    float getDetectionRange() const { return m_detectionRange; }

    void setDamage(float dmg) { damage = dmg; }
    float getDamage() const { return damage; }

    void setAttackSpeed(float speed) { attackSpeed = speed; }
    float getAttackSpeed() const { return attackSpeed; }

    void setSpawnPoint(glm::vec3 pos) { spawnPoint = pos; }
    glm::vec3 getSpawnPoint() const { return spawnPoint; }

    void setRotationOffset(float offset) { RotationOffset = offset; }
};