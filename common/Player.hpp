#include <common/Entity.hpp>
#include <common/Camera.hpp>
#include <common/Model.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Player : public Entity {

private:
    float m_translationSpeed{ 25.0f };
    float m_rotationSpeed{ 0.1f };

public:
    Camera camera;
    Player(std::string filename, Shader shader, Camera camera);
    void updateInput(float deltaTime, GLFWwindow* window);
    void updatePlayer(glm::vec3 pos, glm::vec3 eulerAngle);
};