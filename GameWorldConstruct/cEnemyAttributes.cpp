#include "pch.h"
#include "cEnemyAttributes.h"
#include <cmath>

cEnemyAttributes::cEnemyAttributes(std::string modelName, glm::vec3 position, glm::vec3 forward, float speed, float rotationSpeed)
{
	this->initialEnemyPosition = position;
	this->enemyModelName = modelName;
	this->currentEnemyPosition = position;
	this->oldEnemyPosition = this->currentEnemyPosition;
	this->enemyForward = forward;
	this->enemySpeed = speed;
	this->enemyRotationSpeed = rotationSpeed;
}

// Function to make the enemy move towards the player
void cEnemyAttributes::Seek(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	glm::vec3 direction = glm::normalize(playerAttributes.playerPosition - currentEnemyPosition);

	glm::vec3 orientationDirection = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));

	glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

	// Rotating model using quaternion
	gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

	// Condition to check if the enemy model is not very close to the player
	if (glm::length(currentEnemyPosition - playerAttributes.playerPosition) >= CLOSEST_DISTANCE)
	{
		currentEnemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving model towards player direction
		gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.85f, 0.f, 0.f); // Red
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to make the enemy move away from the player
void cEnemyAttributes::Flee(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	// Condition to check if the player is close enough for the enemy to flee
	if (glm::length(currentEnemyPosition - playerAttributes.playerPosition) < MAINTAIN_DISTANCE)
	{
		glm::vec3 fleeDirection = glm::normalize(currentEnemyPosition - playerAttributes.playerPosition);

		glm::vec3 orientationDirection = glm::normalize(glm::vec3(fleeDirection.x, 0.0f, fleeDirection.z));

		glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

		// Rotating model using quaternion
		gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

		currentEnemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving the enemy away from the player
		gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.f, 0.f, 0.85f); // Blue
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to make the enemy move towards the player's future position
void cEnemyAttributes::Pursue(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	glm::vec3 futurePlayerPosition = playerAttributes.playerPosition + playerAttributes.playerVelocity * TIME_HORIZON;

	glm::vec3 pursueDirection = glm::normalize(futurePlayerPosition - currentEnemyPosition); // Direction for movement

	glm::vec3 direction = glm::normalize(playerAttributes.playerPosition - currentEnemyPosition); // Direction for orientation

	glm::vec3 orientationDirection = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));

	glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

	// Rotating model using quaternion
	gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

	if (glm::length(currentEnemyPosition - futurePlayerPosition) > 10.0f)
	{
		currentEnemyPosition += enemySpeed * pursueDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving model towards player direction
		gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.f, 0.85f, 0.f); // Green
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to make the enemy move away from the player's future position
void cEnemyAttributes::Evade(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	glm::vec3 futurePlayerPosition = playerAttributes.playerPosition + playerAttributes.playerVelocity * TIME_HORIZON;

	if (glm::length(currentEnemyPosition - futurePlayerPosition) < MAINTAIN_DISTANCE)
	{
		glm::vec3 fleeDirection = glm::normalize(currentEnemyPosition - futurePlayerPosition);

		glm::vec3 orientationDirection = glm::normalize(glm::vec3(fleeDirection.x, 0.0f, fleeDirection.z));

		glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

		// Rotating model using quaternion
		gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

		currentEnemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving the enemy away from the player
		gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.85f, 0.85f, 0.f); // Yellow
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to make the enemy maintain distance from the player
void cEnemyAttributes::Approach(cControlGameEngine& gameEngine, sPlayerAttributes& playerAttributes)
{
	float offset = 10.f;

	if (glm::length(currentEnemyPosition - playerAttributes.playerPosition) > MAINTAIN_DISTANCE + offset)
	{
		glm::vec3 direction = glm::normalize(playerAttributes.playerPosition - currentEnemyPosition);

		glm::vec3 orientationDirection = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));

		glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

		// Rotating model using quaternion
		gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

		// Condition to check if the enemy model is not very close to the player
		if (glm::length(currentEnemyPosition - playerAttributes.playerPosition) > MAINTAIN_DISTANCE + offset)
		{
			currentEnemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

			// Moving model towards player direction
			gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

			gameEngine.UseManualColors(enemyModelName, true);
			gameEngine.ChangeColor(enemyModelName, 0.f, 0.85f, 0.85f); // Light Blue
		}
		else
			gameEngine.UseManualColors(enemyModelName, false);
	}

	else if (glm::length(currentEnemyPosition - playerAttributes.playerPosition) < MAINTAIN_DISTANCE)
	{
		glm::vec3 fleeDirection = glm::normalize(currentEnemyPosition - playerAttributes.playerPosition);

		glm::vec3 orientationDirection = glm::normalize(glm::vec3(fleeDirection.x, 0.0f, fleeDirection.z));

		glm::quat rotationQuat = glm::rotation(enemyForward, orientationDirection);

		// Rotating model using quaternion
		gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

		currentEnemyPosition += enemySpeed * orientationDirection * static_cast<float>(gameEngine.deltaTime);

		// Moving the enemy away from the player
		gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, 0.f, 0.85f, 0.85f); // Light Blue
	}
	else
		gameEngine.UseManualColors(enemyModelName, false);
}

// Function to initialize the wander behaviour
void cEnemyAttributes::InitializeWanderBehaviour(unsigned decisionTime, float radius1, float radius2, glm::vec3 wanderColor)
{
	if (this->mWanderBehaviour == NULL)
		this->mWanderBehaviour = new sWanderBehaviorAttributes(decisionTime, radius1, radius2, wanderColor);
	else
	{
		std::cout << std::endl;
		std::cout << "WANDER BEHAVIOUR ALREADY INITIALIZED" << std::endl;
	}
}

// Function to make the enemy wander in the game world region
void cEnemyAttributes::Wander(cControlGameEngine& gameEngine)
{
	this->mWanderBehaviour->wanderCountdown -= gameEngine.deltaTime;

	if (this->mWanderBehaviour->wanderCountdown <= 0.f)
	{
		this->mWanderBehaviour->wanderCountdown = this->mWanderBehaviour->wanderDecisionTime;
		
		glm::vec3 direction = this->enemyForward;
		glm::vec3 wanderPoint(this->currentEnemyPosition + direction * this->mWanderBehaviour->wanderRadius1);

		// Finding a random angle to move to/turn to
		float randomAngle = glm::linearRand(0.f, glm::two_pi<float>());

		float xPos = this->mWanderBehaviour->wanderRadius1 * glm::cos(randomAngle);
		float zPos = this->mWanderBehaviour->wanderRadius2 * glm::sin(randomAngle);

		wanderPoint.x += xPos;
		wanderPoint.z += zPos;

		this->mWanderBehaviour->wanderDirection = glm::normalize(wanderPoint - this->currentEnemyPosition);

		//--------------------Creating a sphere to indicate the wander point in game world-------------------------------
		
		this->IndicateWanderPoint(gameEngine, wanderPoint);
	}

	// Fetching the target rotation direction
	glm::quat targetRotationQuat = glm::rotation(enemyForward, this->mWanderBehaviour->wanderDirection);

	// Fetching the target original rotated direction
	glm::quat rotationQuat = gameEngine.GetModelRotationQuat(this->enemyModelName);
	
	// Fetching the interpolated quat(a rotation direction inbetween the current and target direction)
	glm::quat interpolatedQuat = glm::slerp(glm::normalize(rotationQuat), glm::normalize(targetRotationQuat), this->enemyRotationSpeed * static_cast<float>(gameEngine.deltaTime));

	rotationQuat = interpolatedQuat;

	// Rotating model using quaternion
	gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);

	this->currentEnemyPosition += enemySpeed * this->mWanderBehaviour->wanderDirection * static_cast<float>(gameEngine.deltaTime);

	float BOUNDARY_CHECK = 950.f;

	// Checking if the enemy is leaving the boundary of the game region
	if (this->currentEnemyPosition.x > BOUNDARY_CHECK || this->currentEnemyPosition.x < -BOUNDARY_CHECK || this->currentEnemyPosition.z > BOUNDARY_CHECK || this->currentEnemyPosition.z < -BOUNDARY_CHECK)
		this->currentEnemyPosition = this->initialEnemyPosition;

	// Moving model towards player direction
	gameEngine.MoveModel(enemyModelName, currentEnemyPosition.x, currentEnemyPosition.y, currentEnemyPosition.z);

	// Changing colors to distinguish the models
	if (!this->bColorChanged)
	{
		gameEngine.UseManualColors(enemyModelName, true);
		gameEngine.ChangeColor(enemyModelName, this->mWanderBehaviour->wanderVariationColor.x, this->mWanderBehaviour->wanderVariationColor.y, this->mWanderBehaviour->wanderVariationColor.z);
		
		this->bColorChanged = true;
	}
}

// Function to create spheres to indicate the wander point in the game world
void cEnemyAttributes::IndicateWanderPoint(cControlGameEngine& gameEngine, glm::vec3 wanderPoint)
{
	std::string sphereModelName = "Sphere_" + this->enemyModelName;

	this->DeleteOldPoint(gameEngine, sphereModelName);

	gameEngine.LoadModelsInto3DSpace("Sphere_1_unit_Radius_uv.ply", sphereModelName, wanderPoint.x, 10.f, wanderPoint.z);
	gameEngine.ScaleModel(sphereModelName, 4.5f);
	gameEngine.TurnMeshLightsOn(sphereModelName);
	gameEngine.TurnWireframeModeOn(sphereModelName);
	gameEngine.UseManualColors(sphereModelName, true);
	gameEngine.ChangeColor(sphereModelName, this->mWanderBehaviour->wanderVariationColor.x - 0.1, this->mWanderBehaviour->wanderVariationColor.y - 0.1, this->mWanderBehaviour->wanderVariationColor.z - 0.1);
}

// Function to delete the old sphere model in the previous wander point
void cEnemyAttributes::DeleteOldPoint(cControlGameEngine& gameEngine, std::string sphereModelName)
{
	gameEngine.DeleteMesh(sphereModelName);
}

void cEnemyAttributes::Flock(cControlGameEngine& gameEngine, std::vector <cEnemyAttributes*> enemyAIList)
{
	//-------------------Check Flocking Forces--------------------------

	glm::vec3 separationForce = FlockingSeparation(enemyAIList);
	glm::vec3 alignmentForce = FlockingAlignment(enemyAIList);
	glm::vec3 cohesionForce = FlockingCohesion(enemyAIList);

	this->mFlockingBehaviour->enemyAcceleration += separationForce;
	this->mFlockingBehaviour->enemyAcceleration += alignmentForce;
	this->mFlockingBehaviour->enemyAcceleration += cohesionForce;

	//--------------------Update Enemy Position-------------------------
	
	this->currentEnemyPosition += this->mFlockingBehaviour->enemyVelocity * static_cast<float>(gameEngine.deltaTime);
	this->mFlockingBehaviour->enemyVelocity += this->mFlockingBehaviour->enemyAcceleration;
	//this->mFlockingBehaviour->enemyVelocity = this->LimitMagnitude(this->mFlockingBehaviour->enemyVelocity, this->mFlockingBehaviour->enemyMaxSpeed);

	//---------------Resetting Acceleration to Zero--------------------

	this->mFlockingBehaviour->enemyAcceleration = glm::vec3(0.f);

	//----------------------Check Boundaries----------------------------

	float offsetValue = 0.5f;

	if (this->currentEnemyPosition.x < this->mFlockingBehaviour->minBoundaryX || this->currentEnemyPosition.x > this->mFlockingBehaviour->maxBoundaryX)
	{
		this->mFlockingBehaviour->enemyVelocity.x = -(this->mFlockingBehaviour->enemyVelocity.x);
		this->currentEnemyPosition += this->mFlockingBehaviour->enemyVelocity * static_cast<float>(gameEngine.deltaTime);
		
		if (this->currentEnemyPosition.x < this->mFlockingBehaviour->minBoundaryX)
			this->currentEnemyPosition.x = this->mFlockingBehaviour->minBoundaryX + offsetValue;
		
		if(this->currentEnemyPosition.x > this->mFlockingBehaviour->maxBoundaryX)
			this->currentEnemyPosition.x = this->mFlockingBehaviour->maxBoundaryX - offsetValue;
	}

	if (this->currentEnemyPosition.z < this->mFlockingBehaviour->minBoundaryZ || this->currentEnemyPosition.z > this->mFlockingBehaviour->maxBoundaryZ)
	{
		this->mFlockingBehaviour->enemyVelocity.z = -(this->mFlockingBehaviour->enemyVelocity.z);
		this->currentEnemyPosition += this->mFlockingBehaviour->enemyVelocity * static_cast<float>(gameEngine.deltaTime);

		if (this->currentEnemyPosition.z < this->mFlockingBehaviour->minBoundaryZ)
			this->currentEnemyPosition.z = this->mFlockingBehaviour->minBoundaryZ + offsetValue;

		if (this->currentEnemyPosition.z > this->mFlockingBehaviour->maxBoundaryZ)
			this->currentEnemyPosition.z = this->mFlockingBehaviour->maxBoundaryZ - offsetValue;
	}

	//---------Rotating Enemy towards the moving direction--------------

	glm::vec3 directionOfMovement = glm::normalize(this->mFlockingBehaviour->enemyVelocity);

	glm::quat targetRotationQuat = glm::rotation(this->enemyForward, directionOfMovement);
	glm::quat rotationQuat = gameEngine.GetModelRotationQuat(this->enemyModelName);
	glm::quat interpolatedQuat = glm::slerp(glm::normalize(rotationQuat), glm::normalize(targetRotationQuat), this->enemyRotationSpeed * static_cast<float>(gameEngine.deltaTime));

	rotationQuat = interpolatedQuat;

	//---------------Make changes to the mesh model---------------------

	gameEngine.MoveModel(this->enemyModelName, this->currentEnemyPosition.x, this->currentEnemyPosition.y, this->currentEnemyPosition.z);
	gameEngine.RotateMeshModelUsingQuaternion(enemyModelName, rotationQuat);
}

glm::vec3 cEnemyAttributes::FlockingAlignment(std::vector <cEnemyAttributes*> flockBuddiesList)
{
	glm::vec3 alignmentForce = glm::vec3(0.f);

	float totalEnemiesWithinRange = 0.f;

	//-----------Check distance with other flock buddies----------------

	for (cEnemyAttributes* otherFlockBuddies : flockBuddiesList)
	{
		if (otherFlockBuddies != this)
		{
			float distanceBetweenEnemies = glm::distance(this->currentEnemyPosition, otherFlockBuddies->oldEnemyPosition);

			if (distanceBetweenEnemies < this->mFlockingBehaviour->flockMaxRadius)
			{
				alignmentForce += otherFlockBuddies->mFlockingBehaviour->enemyVelocity;
				totalEnemiesWithinRange++;
			}
		}
	}

	if (totalEnemiesWithinRange > 0)
	{
		//--------------Calculating the steering velocity-------------------

		alignmentForce /= totalEnemiesWithinRange;
		alignmentForce = this->SetMagnitude(alignmentForce);
		alignmentForce -= this->mFlockingBehaviour->enemyVelocity;
		alignmentForce = this->LimitMagnitude(alignmentForce, this->mFlockingBehaviour->enemyMaxForce);
	}

	return alignmentForce;
}

glm::vec3 cEnemyAttributes::FlockingCohesion(std::vector <cEnemyAttributes*> flockBuddiesList)
{
	glm::vec3 cohesionForce = glm::vec3(0.f);

	float totalEnemiesWithinRange = 0.f;

	//-----------Check distance with other flock buddies----------------

	for (cEnemyAttributes* otherFlockBuddies : flockBuddiesList)
	{
		if (otherFlockBuddies != this)
		{
			float distanceBetweenEnemies = glm::distance(this->currentEnemyPosition, otherFlockBuddies->oldEnemyPosition);

			if (distanceBetweenEnemies < this->mFlockingBehaviour->flockMaxRadius)
			{
				cohesionForce += otherFlockBuddies->oldEnemyPosition;
				totalEnemiesWithinRange++;
			}
		}
	}

	if (totalEnemiesWithinRange > 0)
	{
		//--------------Calculating the steering velocity-------------------

		cohesionForce /= totalEnemiesWithinRange;
		cohesionForce -= this->currentEnemyPosition;
		cohesionForce = this->SetMagnitude(cohesionForce);
		cohesionForce -= this->mFlockingBehaviour->enemyVelocity;
		cohesionForce = this->LimitMagnitude(cohesionForce, this->mFlockingBehaviour->enemyMaxForce);
	}

	return cohesionForce;
}

glm::vec3 cEnemyAttributes::FlockingSeparation(std::vector <cEnemyAttributes*> flockBuddiesList)
{
	glm::vec3 separationForce = glm::vec3(0.f);

	float totalEnemiesWithinRange = 0.f;

	//-----------Check distance with other flock buddies----------------

	for (cEnemyAttributes* otherFlockBuddies : flockBuddiesList)
	{
		if (otherFlockBuddies != this)
		{
			float distanceBetweenEnemies = glm::distance(this->currentEnemyPosition, otherFlockBuddies->oldEnemyPosition);

			if (distanceBetweenEnemies < this->mFlockingBehaviour->flockMaxRadius)
			{
				glm::vec3 positionDifference = this->currentEnemyPosition - otherFlockBuddies->oldEnemyPosition;
				positionDifference /= distanceBetweenEnemies;

				separationForce += positionDifference;
				totalEnemiesWithinRange++;
			}
		}
	}

	if (totalEnemiesWithinRange > 0)
	{
		//--------------Calculating the steering velocity-------------------

		separationForce /= totalEnemiesWithinRange;
		separationForce = this->SetMagnitude(separationForce);
		separationForce -= this->mFlockingBehaviour->enemyVelocity;
		separationForce = this->LimitMagnitude(separationForce, this->mFlockingBehaviour->enemyMaxForce);
	}

	return separationForce;
}

glm::vec3 cEnemyAttributes::SetMagnitude(glm::vec3 steeringVelocity)
{
	//float velocityX = steeringVelocity.x;
	//float velocityZ = steeringVelocity.z;

	//double magnitude = sqrt(velocityX * velocityX + velocityZ * velocityZ);

	//double scaleFactor = this->mFlockingBehaviour->enemyMaxSpeed / magnitude;

	//steeringVelocity.x *= scaleFactor;
	//steeringVelocity.z *= scaleFactor;

	float currentMagnitude = glm::length(steeringVelocity);

	if (currentMagnitude != 0)
		steeringVelocity = steeringVelocity * (this->mFlockingBehaviour->enemyMaxSpeed / currentMagnitude);

	return steeringVelocity;
}

glm::vec3 cEnemyAttributes::LimitMagnitude(glm::vec3 steeringVelocity, float maxSpeed)
{
	float magnitudeSquared = glm::dot(steeringVelocity, steeringVelocity);

	if (magnitudeSquared > maxSpeed * maxSpeed)
	{
		float scaleFactor = maxSpeed / sqrt(magnitudeSquared);
		steeringVelocity *= scaleFactor;
	}

	return steeringVelocity;
}

void cEnemyAttributes::InitializeFlockingAttributes(glm::vec3 velocity, glm::vec3 acceleration, float flockRadius, float maxForce, float boundaryValue)
{
	if(this->mFlockingBehaviour == NULL)
		this->mFlockingBehaviour = new sFlockingBehaviourAttributes(velocity, acceleration, this->enemySpeed, flockRadius, maxForce, boundaryValue);
}

