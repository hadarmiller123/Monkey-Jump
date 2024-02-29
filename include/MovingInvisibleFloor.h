#pragma once
//-------------------------------------------//
#include "MovingFloor.h"
#include "Resources.h"
#include "Factory.h"
//-------------------------------------------//
class MovingInvisibleFloor : public MovingFloor
{
public:
	MovingInvisibleFloor(const sf::Vector2f& Position);
	virtual void Move() override;
	virtual void Collided(const BaseGameObject& GivenCollidedObject) override;
	virtual void UpdateMyVisibilityStatus(const Monkey& GivenMonkey) override;
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