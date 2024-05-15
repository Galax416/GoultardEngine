#pragma once

#include <common/Entity.hpp>
#include <common/Weapon.hpp>
#include <common/Utils.hpp>

#include <irrKlang.h>

static glm::vec3 cameraOffset(0.f, 83.f, 25.f); // offset from the player position
static glm::vec3 weaponOffset(-20.0f, 70.0f, 65.0f); // offset from the player position
static glm::vec3 bulletOffset = weaponOffset - cameraOffset; // offset from the camera position

class Player : public Entity {

private:
    float m_translationSpeed{ 250.0f };
    float m_rotationSpeed{ 2.5f };
    float m_health{ 100 };
    float m_maxHealth{ 100 };

    glm::vec3 m_lastValidPosition;
    glm::vec3 m_normalCollision;

    float m_heightGround{ 0.0f };

    bool m_jumpKeyPressed{ false };
    bool m_isSprinting{ false };

    // Sound
    irrklang::ISoundEngine* m_soundEngine;
    float lastPlayed{ 0.0f }; // footstep sound

public:
    Camera camera;
    Weapon* weapon;

    Player(std::string filename, Shader *shader, Camera camera);
    Player(Model *model, Shader *shader, Camera camera);

    void updateInput(bool isColliding=false, float deltaTime=0.0f, GLFWwindow* window=nullptr);
    void updatePlayer(bool isColliding=false, glm::vec3 pos=glm::vec3(0.0f), glm::vec3 eulerAngle=glm::vec3(0.0f));
    void update(bool isColliding, float deltaTime, GLFWwindow* window);

    // Mvt
    void jump(float jumpSpeed);
    
    void respawn(glm::vec3 pos);

    void setNormalCollision(glm::vec3 n) { m_normalCollision = n; }

    bool CheckCollisionWithEntity(Entity &entity);
    bool CheckCollisionWithSingleEntity(Entity &entity);

    void setWeapon(Weapon* weapon) { this->weapon = weapon; }

    void setHealth(int health) { m_health = health;};
    float& getHealth() { return m_health;} ;
    int getMaxHealth() { return m_maxHealth; }

    void setSoundEngine(irrklang::ISoundEngine* soundEngine) { m_soundEngine = soundEngine; }
};