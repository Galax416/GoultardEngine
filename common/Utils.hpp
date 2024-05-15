#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

static glm::vec3 VEC_ZERO{ 0.f,0.f,0.f };
static glm::vec3 VEC_UP{ 0.f,1.f,0.f };
static glm::vec3 VEC_FRONT{ 0.f,0.f,1.f };
static glm::vec3 VEC_RIGHT{ 1.f,0.f,0.f };

enum InterpolationType {
    SMOOTHSTEP,
    COSINUS,
    EXPONENTIAL,
    LOGARITHMIC
};

static float clipAngle180(float angle) {
    return std::fmod(angle + 180.0f, 360.0f) - 180.0f;
}

static glm::vec3 projectVectorOnPlan(glm::vec3 vector, glm::vec3 normalPlan) {
    return glm::cross(normalPlan, glm::cross(vector, normalPlan));
}

static glm::vec3 quatToEuler(glm::quat _quat) {
	// Opengl quat to euler function give yaw betweel -90 and 90
	// If you want correct pitch and yaw you can use this 
	// Src http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
	// But roll will be bewteen -90 and 90 here

	glm::vec3 eulerAngles;

	float test = _quat.x * _quat.y + _quat.z * _quat.w;

	if (test > 0.499f) { // singularity at north pole
		eulerAngles.y = 2.f * atan2(_quat.x, _quat.w);
		eulerAngles.z = M_PI / 2.f;
		eulerAngles.x = 0.f;
		return eulerAngles;
	}
	if (test < -0.499f) { // singularity at south pole
		eulerAngles.y = -2.f * atan2(_quat.x, _quat.w);
		eulerAngles.z = -M_PI / 2.f;
		eulerAngles.x = 0.f;
		return eulerAngles;
	}
	float sqx = _quat.x * _quat.x;
	float sqy = _quat.y * _quat.y;
	float sqz = _quat.z * _quat.z;


	eulerAngles.y = atan2(2.f * _quat.y * _quat.w - 2.f * _quat.x * _quat.z, 1.f - 2.f * sqy - 2.f * sqz);
	eulerAngles.z = asin(2.f * test);
	eulerAngles.x = atan2(2.f * _quat.x * _quat.w - 2.f * _quat.y * _quat.z, 1.f - 2.f * sqx - 2.f * sqz);

	return eulerAngles;
}

static float interpolate(float ratio, InterpolationType type) {
	switch (type) {
        case SMOOTHSTEP:
            return ratio * ratio * (3 - 2 * ratio); // Interpolation smooth
        case COSINUS:
            return 0.5f * (1.0f - cos(ratio * M_PI));
        case EXPONENTIAL:
            return exp(ratio) / exp(1.0f); // Interpolation exponentielle
        case LOGARITHMIC:
            return log(ratio * (glm::e<float>() - 1.0f) + 1.0f) / log(glm::e<float>()); // Interpolation logarithmique
        default:
            return ratio; // Interpolation linéaire, pas de modification
    }
}

static glm::quat extractYaw(const glm::quat& quat) {
    // Convertir le quaternion en matrice de rotation
    glm::mat4 rotationMatrix = glm::toMat4(quat);

    // Extraire l'angle de rotation autour de l'axe Y (yaw)
    float yaw = atan2(rotationMatrix[2][0], rotationMatrix[0][0]);

    // Créer un quaternion représentant uniquement la rotation autour de l'axe Y
    glm::quat yawQuat = glm::angleAxis(yaw, VEC_UP);

    return yawQuat;
}



