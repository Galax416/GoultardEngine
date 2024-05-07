#include <common/Bullet.hpp>

Bullet::Bullet(Model* model, Shader *shader) : Entity("", shader) {
    this->model = model;
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
	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "Model"), 1, GL_FALSE, &transform.getModelMatrix()[0][0]); // Model Matrix

    model->Draw(shader);
}