#include <common/Bullet.hpp>

Bullet::Bullet(Model* modelptr, Shader *shader) : Entity("", shader) {
    this->model = modelptr;
}

void Bullet::update(float deltaTime) {
    if (isAlive()) {
        transform.setLocalPosition(transform.getLocalPosition() + getDirection() * getSpeed() * deltaTime);
        transform.computeModelMatrix();
        render();
        setLifeTime(getLifeTime() - deltaTime);

        if (getLifeTime() <= 0) {
            setAlive(false);
        }
    }
}

void Bullet::render() {

    shader->use();
    shader->setMat4("Model", transform.getModelMatrix()); // Model Matrix

    model->Draw(shader);
}