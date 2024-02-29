#pragma once
//-------------------------------------------//
#include "MovingFloor.h"
#include "Resources.h"
#include "Factory.h"
//-------------------------------------------//
class MovingCloudFloor : public MovingFloor
{
public:
	MovingCloudFloor(const sf::Vector2f& Position);
	virtual void Move() override;
	virtual void Collided(const BaseGameObject& GivenCollidedObject) override;
private:
	void SetLeftMovement();
	void SetRightMovement();
private:
	bool m_ChangeDefaultMovementSides = false;
	float m_LeftMovementSpeed = -4.0;
	float m_RightMovementSpeed = 4.0;
	bool m_LeftMovement = true;
	bool m_RightMovement = false;
};
//-------------------------------------------//