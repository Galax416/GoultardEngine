#include <common/Weapon.hpp>

// Weapon::Weapon(std::string filename, Shader *shader) : Entity(filename, shader), bulletModel("") {}
Weapon::Weapon(std::string filename, Shader *shader, std::string bulletPath) : Entity(filename, shader), bulletModel(bulletPath) {
}

void Weapon::updateBullets(float deltaTime) {
    for (auto& bullet : bullets) {
        if (bullet->isAlive()) {
            bullet->update(deltaTime);
        }
    }
    // Remove dead bullets
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet* b) { if (!b->isAlive()) {delete(b); return true;} return false;}), bullets.end());
}

void Weapon::shoot(glm::vec3 position, glm::vec3 direction, glm::vec3 rotation, glm::vec3 offset, float speed, float lifeTime) {
    if (glfwGetTime() - lastShootTime >= fireRate && ammo > 0) { // Fire rate
        lastShootTime = glfwGetTime();
        Bullet* bullet = new Bullet(&bulletModel, shader);

        glm::vec3 rotationbullet = glm::vec3(0.0f, -90.0f, 00.0f); // make the bullet face the right direction
        glm::vec3 fixedAngle = glm::vec3(rotation.z, rotation.y, -rotation.x); // it just works
        bullet->transform.setLocalRotation(rotationbullet + fixedAngle); // Set bullet rotation

        glm::quat rotationQuat = glm::angleAxis(glm::radians(-fixedAngle.y), VEC_UP);
        glm::vec3 rotationoff = offset * rotationQuat;
        bullet->transform.setLocalPosition(rotationoff + position); // Set bullet position

        bullet->transform.setLocalScale(glm::vec3(1.5f, 1.5f, 1.5f));

        bullet->setDirection(direction);
        bullet->setSpeed(speed);
        bullet->setLifeTime(lifeTime);
        bullet->setAlive(true);
        bullet->setDamage(20.0f);
        bullets.push_back(bullet);
        bullet->parent = this;

        m_soundEngine->play2D("../data/sound/gun.wav", false);

        ammo--;
    }
    if (ammo == 0) std::cout << "Out of ammo" << std::endl;
}

void Weapon::reload() {
    if (glfwGetTime() - lastReloadTime >= reloadTime && ammo < maxAmmo) {
        lastReloadTime = glfwGetTime();
        ammo = maxAmmo;
    }
}