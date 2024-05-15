#pragma once

#include <common/Entity.hpp>
#include <common/Model.hpp>
#include <common/Bullet.hpp>
#include <common/Utils.hpp>

#include <irrKlang.h>

class Weapon : public Entity {

private:
    float reloadTime{ 0.5f };
    float lastReloadTime{ 0.0f };
    float fireRate{ 0.3f };
    float lastShootTime{ 0.0f };
    int ammo{ 30 };
    int maxAmmo{ 30 };

    std::vector<Bullet*> bullets; // Bullets fired by the weapon
    Model bulletModel; // Model of the bullet

    irrklang::ISoundEngine* m_soundEngine;

public:
    Weapon(std::string filename, Shader *shader); // Constructor no bullet
    Weapon(std::string filename, Shader *shader, std::string bulletPath); // Constructor with bullet
    Weapon(Shader *shader);

    void addChild(Bullet& child);

    void shoot(glm::vec3 position, glm::vec3 direction, glm::vec3 rotation, glm::vec3 offset, float speed, float lifeTime);
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

    // bullets
    std::vector<Bullet*> getBullets() const {return bullets;}

    void setSoundEngine(irrklang::ISoundEngine* soundEngine) { m_soundEngine = soundEngine; }
};