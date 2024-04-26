#include <common/Entity.hpp>
#include <common/Camera.hpp>
#include <common/Model.hpp>

class Player : public Entity {

private:


public:
    Camera camera;
    Player(std::string filename, Shader shader, Camera camera);
    void render();
};