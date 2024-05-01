#pragma once

#include <common/Entity.hpp>
#include <common/Model.hpp>
#include <common/Bullet.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Weapon : public Entity {

private:
    float reloadTime{ 0.5f };
    float lastReloadTime{ 0.0f };
    float fireRate{ 0.2f };
    float lastShootTime{ 0.0f };
    int ammo{ 30 };
    int maxAmmo{ 30 };

    std::vector<Bullet*> bullets; // Bullets fired by the weapon
    std::string bulletPath; // Path to the bullet model

public:
    Weapon(std::string filename, Shader *shader); // Constructor no bullet
    Weapon(std::string filename, Shader *shader, std::string bulletPath); // Constructor with bullet
    Weapon(Shader *shader);

    void shoot(glm::vec3 position, glm::vec3 direction, float speed, float lifeTime);
    void updateBullets(float deltaTime);

    void reload();

    // reloadTime
    float getReloadTime() const {return reloadTime;}
    void setReloadTime(float time) {reloadTime = time;}

    // fireRate
    float getFireRate() const {return fireRate;}
    void setFireRate(float rate) {fireRate = rate;}

    // ammo
    int getAmmo() const {return ammo;}
    void setAmmo(int amount) {ammo = amount;}

    // maxAmmo
    int getMaxAmmo() const {return maxAmmo;}
    void setMaxAmmo(int amount) {maxAmmo = amount;}
};