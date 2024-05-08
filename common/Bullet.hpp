#pragma once

#include <common/Entity.hpp>

class Bullet : public Entity {

private:
    glm::vec3 direction;
    glm::vec3 rotation;
    float speed;
    float lifeTime;
    bool Alive;

    Model *modelptr;

public:
    Bullet(Model *modelptr, Shader *shader);
    void update(float deltaTime);
    void render();

    glm::vec3 getDirection() const { return direction; }
    void setDirection(const glm::vec3& newDirection) { direction = newDirection; }

    glm::vec3 getRotation() const { return rotation; }
    void setRotation(const glm::vec3& newRotation) { rotation = newRotation; }

    float getSpeed() const { return speed; }
    void setSpeed(float newSpeed) { speed = newSpeed; }

    float getLifeTime() const { return lifeTime; }
    void setLifeTime(float newLifeTime) { lifeTime = newLifeTime; }

    bool isAlive() const { return Alive; }
    void setAlive(bool newIsAlive) { Alive = newIsAlive; }
};