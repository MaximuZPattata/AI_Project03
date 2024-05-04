#pragma once

enum class ePlayerDirection
{
	FRONT,
	BACK,
	LEFT,
	RIGHT
};

struct sPlayerAttributes
{
	sPlayerAttributes(const glm::vec3& position, float yaw, std::string modelName, float speed)
		: playerPosition(position)
		, playerYaw(yaw)
		, playerModelName(modelName) 
		, playerSpeed(speed) {}

	glm::vec3 playerPosition;
	glm::vec3 playerVelocity = glm::vec3(0.f);
	float playerYaw;
	std::string playerModelName;
	float playerSpeed;
	ePlayerDirection playerDirection = ePlayerDirection::FRONT;
};
