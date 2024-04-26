#include <common/Player.hpp>

Player::Player(std::string filename, Shader shader, Camera camera) : Entity(filename, shader) {
    camera.setEditionMode(false);
    this->camera = camera;
}

void Player::render() {
    glUseProgram(program_scene);
	//glUniformMatrix4fv(glGetUniformLocation(program_scene, "Model"), 1, GL_FALSE, &transform.getModelMatrix()[0][0]); // Model Matrix

	// Draw Mesh
	model.Draw(shader); // Render geometry

	for (auto&& child : children) {
		child->render();
	}
}