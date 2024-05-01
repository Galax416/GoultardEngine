#include <common/Weapon.hpp>

Weapon::Weapon(std::string filename, Shader *shader) : Entity(filename, shader) {}
Weapon::Weapon(std::string filename, Shader *shader, std::string bulletPath) : Entity(filename, shader) {
    this->bulletPath = bulletPath;
}
Weapon::Weapon(Shader *shader) : Entity(shader) {}

void Weapon::updateBullets(float deltaTime) {
    for (auto& bullet : bullets) {
        if (bullet->isAlive()) {
            bullet->update(deltaTime);
        }
    }
    // Remove dead bullets
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet* b) { if (!b->isAlive()) {delete(b); return true;} return false;}), bullets.end());
}

void Weapon::shoot(glm::vec3 position, glm::vec3 direction, float speed, float lifeTime) {
    if (glfwGetTime() - lastShootTime >= fireRate && ammo > 0) { // Fire rate
        lastShootTime = glfwGetTime();
        Bullet* bullet = new Bullet(bulletPath, shader);
        bullet->transform.setLocalPosition(position); // Set bullet position
        bullet->setDirection(direction);
        bullet->setSpeed(speed);
        bullet->setLifeTime(lifeTime);
        bullet->setAlive(true);
        bullets.push_back(bullet);
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