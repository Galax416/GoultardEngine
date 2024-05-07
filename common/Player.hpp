#pragma once

#include <common/Entity.hpp>
#include <common/Weapon.hpp>
#include <common/text2D.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Player : public Entity {

private:
    float m_translationSpeed{ 150.0f };
    float m_rotationSpeed{ 2.5f };
    int m_health{ 100 };

    glm::vec3 m_lastValidPosition;
    glm::vec3 m_normalCollision;

public:
    Camera camera;
    Weapon weapon; // Weapon used 

    Player(std::string filename, Shader *shader, Camera camera);

    void updateInput(bool isColliding=false, float deltaTime=0.0f, GLFWwindow* window=nullptr);
    void updatePlayer(bool isColliding=false, glm::vec3 pos=glm::vec3(0.0f), glm::vec3 eulerAngle=glm::vec3(0.0f));

    void setNormalCollision(glm::vec3 n) { m_normalCollision = n; }

    bool CheckCollisionWithEntity(Entity &entity);
    bool CheckCollisionWithSingleEntity(Entity &entity);

    void setWeapon(Weapon weapon) { this->weapon = weapon; };

    void setHealth(int health) { m_health = health;};
    int getHealth() const { return m_health;} ;

    void initHUD(GLuint shaderID);
    void DrawHUD();
};