#include <common/Weapon.hpp>

Weapon::Weapon(std::string filename, Shader shader) : Entity(filename, shader) {}
Weapon::Weapon(Shader shader) : Entity(shader){}

void Weapon::drawBullets() {
    for (auto bullet : bullets) {
        if (bullet.isAlive) {
            glPushMatrix();
            glTranslatef(bullet.position.x, bullet.position.y, bullet.position.z);

            glBegin(GL_QUADS);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(-100.1f, -100.1f, 100.0f);
            glVertex3f( 100.1f, -100.1f, 100.0f);
            glVertex3f( 100.1f,  100.1f, 100.0f);
            glVertex3f(-100.1f,  100.1f, 100.0f);
            glEnd();

            glPopMatrix();
        }
    }
}

void Weapon::updateBullets(float deltaTime) {
    for (auto& bullet : bullets) {
        if (bullet.isAlive) {
            bullet.position += bullet.direction * bullet.speed * deltaTime;
            std::cout << "bullet.position: " << bullet.position.x << " " << bullet.position.y << " " << bullet.position.z << std::endl;
            bullet.lifeTime -= deltaTime;
            if (bullet.lifeTime <= 0) {
                bullet.isAlive = false;
            }
        }
    }
    // Remove dead bullets
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet b) { return !b.isAlive; }), bullets.end());
}

void Weapon::shoot(glm::vec3 position, glm::vec3 direction, float speed, float lifeTime) {
    if (glfwGetTime() - lastShootTime >= fireRate && ammo > 0) {
        std::cout << "shoot" << std::endl;
        lastShootTime = glfwGetTime();
        Bullet bullet;
        bullet.position = position;
        bullet.direction = direction;
        bullet.speed = speed;
        bullet.lifeTime = lifeTime;
        bullet.isAlive = true;
        bullets.push_back(bullet);
        ammo--;
    }
}