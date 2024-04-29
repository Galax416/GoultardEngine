#pragma once

#include <common/Entity.hpp>
#include <common/Weapon.hpp>
#include <common/text2D.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Player : public Entity {

private:
    float m_translationSpeed{ 50.0f };
    float m_rotationSpeed{ 0.1f };
    bool isCameraUsed{ true };
    int m_health{ 100 };

public:
    Camera camera;
    Weapon weapon; // Weapon used 

    Player(std::string filename, Shader shader, Camera camera);

    void updateInput(float deltaTime, GLFWwindow* window);
    void updatePlayer(glm::vec3 pos, glm::vec3 eulerAngle);

    void setWeapon(Weapon weapon) { this->weapon = weapon; };

    void setHealth(int health) { m_health = health;};
    int getHealth() const { return m_health;} ;

    void initHUD(GLuint shaderID);
    void DrawHUD();
};