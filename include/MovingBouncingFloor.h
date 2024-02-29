#pragma once
//-------------------------------------------//
#include "MovingFloor.h"
#include "Resources.h"
#include "Factory.h"
//-------------------------------------------//
class MovingBouncingFloor : public MovingFloor
{
public:
	MovingBouncingFloor(const sf::Vector2f& Position);
	virtual void Move() override;
	virtual void Collided(const BaseGameObject& GivenCollidedObject) override;

	// overriding Draw function in order to make the sprite stretch effect
	virtual void Draw(sf::RenderWindow& GivenScreen) override;

	// If a collision with monkey happend true is set to m_IsBouncing
	void SetBouncingStatus();
private:
	void SetLeftMovement();
	void SetRightMovement();
private:
	bool m_ChangeDefaultMovementSides = false;
	float m_LeftMovementSpeed = -6.0;
	float m_RightMovementSpeed = 6.0;
	bool m_LeftMovement = true;
	bool m_RightMovement = false;
	bool m_IsBouncing = false;
};
//-------------------------------------------//