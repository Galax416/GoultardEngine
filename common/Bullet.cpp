#include <common/Bullet.hpp>

Bullet::Bullet(std::string filename, Shader *shader) : Entity(filename, shader) {
    transform.setLocalScale(glm::vec3(5.0f));
}

void Bullet::update(float deltaTime) {
    if (isAlive()) {
        transform.setLocalPosition(transform.getLocalPosition() + getDirection() * getSpeed() * deltaTime);
        std::cout << "Bullet position: " << transform.getLocalPosition().x << " " << transform.getLocalPosition().y << " " << transform.getLocalPosition().z << std::endl;
        setLifeTime(getLifeTime() - deltaTime);
        if (getLifeTime() <= 0) {
            setAlive(false);
        }
        else render();
    }
}

void Bullet::render() {

    shader->use();
	glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "Model"), 1, GL_FALSE, &transform.getModelMatrix()[0][0]); // Model Matrix

    model.Draw(shader);
}