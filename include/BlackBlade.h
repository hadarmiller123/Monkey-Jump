#pragma once
//-------------------------------------------//
#include "Blade.h"
#include "Resources.h"
#include "Factory.h"
//-------------------------------------------//
class BlackBlade : public Blade
{
public:
	BlackBlade(const sf::Vector2f& Position);
	virtual void Move() override;
	virtual void Collided(const BaseGameObject& GivenCollidedObject) override;
private:
	void SetLeftMovement();
	void SetRightMovement();
private:
	// For scaling the 200x200 object sprite
	float m_XScale = 0.35f;
	float m_YScale = 0.35f;

	float m_LeftMovementSpeed = -5.0;
	float m_RightMovementSpeed = 5.0;
	bool m_LeftMovement = true;
	bool m_RightMovement = false;
};
//-------------------------------------------//