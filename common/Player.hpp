#pragma once

#include <common/Entity.hpp>
#include <common/Weapon.hpp>
#include <common/text2D.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

static glm::vec3 cameraOffset(0.f, 83.f, 15.f); // offset from the player position
static glm::vec3 weaponOffset(-20.0f, 70.0f, 60.0f); // offset from the player position
static glm::vec3 bulletOffset = weaponOffset - cameraOffset; // offset from the camera position

class Player : public Entity {

private:
    float m_translationSpeed{ 50.0f };
    float m_rotationSpeed{ 0.1f };
    int m_health{ 100 };

    glm::vec3 m_lastValidPosition;
    glm::vec3 m_normalCollision;

public:
    Camera camera;
    Weapon* weapon;

    Player(std::string filename, Shader *shader, Camera camera);

    void updateInput(bool isColliding=false, float deltaTime=0.0f, GLFWwindow* window=nullptr);
    void updatePlayer(bool isColliding=false, glm::vec3 pos=glm::vec3(0.0f), glm::vec3 eulerAngle=glm::vec3(0.0f));

    void setNormalCollision(glm::vec3 n) { m_normalCollision = n; }

    bool CheckCollisionWithEntity(Entity &entity);
    bool CheckCollisionWithSingleEntity(Entity &entity);

    void setWeapon(Weapon* weapon) { this->weapon = weapon; }

    void setHealth(int health) { m_health = health;};
    int getHealth() const { return m_health;} ;

    void initHUD(GLuint shaderID);
    void DrawHUD();
};