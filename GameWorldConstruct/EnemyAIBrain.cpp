#include "pch.h"
#include "cEnemyAttributes.h"
#include <random>


extern std::vector<cEnemyAttributes*> enemyDetailsList;

double getRandom(double min, double max) 
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	
	std::uniform_real_distribution<double> dis(min, max);

	return dis(gen);
}

void InitializingEnemyAIs()
{
	//---------------------------Creating Enemy AI------------------------------------------

	glm::vec3 enemyPosition;
	glm::vec3 randomVelocity;
	glm::vec3 enemyForward = glm::vec3(-1.f, 0.f, 0.f);

	float maxSpeed = 15.f;
	float rotationSpeed = 3.f;
	float commonRadius = 25.f;
	float commonMaxForce = 5.f;
	float minValue = -10.f;
	float maxValue = 10.f;
	float boundaryValue = 100.f;
	float randomInitialSpeed = 5.f;

	for (int enemyCount = 1; enemyCount <= 30; enemyCount++)
	{
		std::string modelName = "Beholder0" + std::to_string(enemyCount);

		enemyPosition = glm::vec3(getRandom(-70.f, 70.f), 10.f, getRandom(-70.f, 70.f));

		cEnemyAttributes* enemy = new cEnemyAttributes(modelName, enemyPosition, enemyForward, maxSpeed, rotationSpeed);

		randomVelocity = glm::vec3(getRandom(minValue, maxValue), 0.f, getRandom(minValue, maxValue));

		randomVelocity *= randomInitialSpeed;

		enemy->InitializeFlockingAttributes(randomVelocity, glm::vec3(0.f), commonRadius, commonMaxForce, boundaryValue);

		enemyDetailsList.push_back(enemy);
	}

	//-----------------------Initialize Wander Behavior-------------------------------------

	//// Giving each wander variation a color
	//glm::vec3 GreenColor = glm::vec3(0.1, 0.85, 0.1);
	//glm::vec3 WhiteColor = glm::vec3(0.9, 0.9, 0.9);
	//glm::vec3 BlueColor = glm::vec3(0.1, 0.1, 0.85);

	//enemy01.InitializeWanderBehaviour(2.5f, 5.f, 2.f, GreenColor);	// Change parameters for distinct wandering style
	//enemy02.InitializeWanderBehaviour(5.0f, 3.f, 5.f, WhiteColor);	// Change parameters for distinct wandering style
	//enemy03.InitializeWanderBehaviour(1.0f, 7.f, 7.f, BlueColor);	// Change parameters for distinct wandering style

	//enemyDetailsList.push_back(enemy01);
	//enemyDetailsList.push_back(enemy02);
	//enemyDetailsList.push_back(enemy03);
}

void UpdateAIPositions()
{
	for (cEnemyAttributes* currentEnemy : enemyDetailsList)
		currentEnemy->oldEnemyPosition = currentEnemy->currentEnemyPosition;
}