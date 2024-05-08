#pragma once

#include <common/Entity.hpp>
#include <common/Weapon.hpp>
#include <common/text2D.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Monster : public Entity {

private:
    float m_translationSpeed{ 150.0f };
    float m_rotationSpeed{ 2.5f };
    int m_health{ 100 };
    float m_detectionRange{ 1400.0f };

    glm::vec3 m_lastValidPosition;
    // glm::vec3 m_normalCollision;

public:
    Monster(std::string filename, Shader *shader);

    void updateMonster(bool isColliding=false, glm::vec3 pos=glm::vec3(0.0f), glm::vec3 eulerAngle=glm::vec3(0.0f), float deltaTime=0.0f);

    // void setNormalCollision(glm::vec3 n) { m_normalCollision = n; }

    void detectPlayer(glm::vec3 playerPos, float deltaTime);

    // bool CheckCollisionWithEntity(Entity &entity);
    // bool CheckCollisionWithSingleEntity(Entity &entity);

    void setHealth(int health) { this->m_health = health;};
    int getHealth() const { return m_health;} ;

};