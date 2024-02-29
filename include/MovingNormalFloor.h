#pragma once
//-------------------------------------------//
#include "MovingFloor.h"
#include "Resources.h"
//-------------------------------------------//
class MovingNormalFloor : public MovingFloor
{
public:
	MovingNormalFloor(const sf::Vector2f& Position);
	virtual void Move() override;
	virtual void Collided(const BaseGameObject& GivenCollidedObject) override;
private:
	void SetLeftMovement();
	void SetRightMovement();
private:
	float m_LeftMovementSpeed = -5.0;
	float m_RightMovementSpeed = 5.0;
	bool m_LeftMovement = true;
	bool m_RightMovement = false;
};
//-------------------------------------------//