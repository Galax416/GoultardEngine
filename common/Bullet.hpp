#pragma once

#include <common/Entity.hpp>

class Bullet : public Entity {

private:
    glm::vec3 direction;
    float speed;
    float lifeTime;
    bool Alive;

public:
    Bullet(std::string filename, Shader *shader);
    void update(float deltaTime);
    void render();

    glm::vec3 getDirection() const { return direction; }
    void setDirection(const glm::vec3& newDirection) { direction = newDirection; }

    float getSpeed() const { return speed; }
    void setSpeed(float newSpeed) { speed = newSpeed; }

    float getLifeTime() const { return lifeTime; }
    void setLifeTime(float newLifeTime) { lifeTime = newLifeTime; }

    bool isAlive() const { return Alive; }
    void setAlive(bool newIsAlive) { Alive = newIsAlive; }
};