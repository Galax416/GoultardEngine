#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera() {};
    Camera(glm::vec3 pos) : camera_position(pos) {}
    Camera(glm::vec3 pos, glm::vec3 target) : camera_position(pos), camera_target(target) {}

    inline float getFovAngle () const { return fovAngle; }
    inline void setFovAngle (float newFovAngle) { fovAngle = newFovAngle; }
    inline float getAspectRatio () const { return aspectRatio; }
    inline float getNearPlane () const { return nearPlane; }
    inline void setNearPlane (float newNearPlane) { nearPlane = newNearPlane; }
    inline float getFarPlane () const { return farPlane; }
    inline void setFarPlane (float newFarPlane) { farPlane = newFarPlane; }

    inline glm::vec3 getPosition () const { return camera_position; }
    inline void setPosition (glm::vec3 pos) { camera_position = pos; }
    inline glm::vec3 getTarget () const { return camera_target; }
    inline void setTarget (glm::vec3 target) { camera_target = target; }
    inline glm::vec3 getUp () const { return camera_up; }
    inline void setUp (glm::vec3 up) { camera_up = up; }

    inline float getCameraSpeed () const { return cameraSpeed; }
    inline void setCameraSpeed (float speed) { cameraSpeed = speed; }


    inline glm::mat4 getProjectionMatrix() { return glm::perspective(glm::radians(fovAngle), aspectRatio, nearPlane, farPlane); }

    inline void moveUp() { camera_position += cameraSpeed * camera_up; }
    inline void moveDown() { camera_position -= cameraSpeed * camera_up; }
    inline void moveLeft() { camera_position -= glm::normalize(glm::cross(camera_target, camera_up)) * cameraSpeed; }
    inline void moveRight() { camera_position += glm::normalize(glm::cross(camera_target, camera_up)) * cameraSpeed; }
    inline void moveFoward() { camera_position += cameraSpeed * camera_target; }
    inline void moveBackward() { camera_position -= cameraSpeed * camera_target; }
  

private:
    float fovAngle = 45.0;
    float aspectRatio = 4/3;
    float nearPlane = 0.1f;
    float farPlane = 10000.0f;
    
    float cameraSpeed = 2.5f;

    glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camera_up = glm::vec3(0.0f, 1.0f,  0.0f);

};





#endif