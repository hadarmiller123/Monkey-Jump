#pragma once
//-------------------------------------------//
#include "Blade.h"
#include "Resources.h"
#include "Factory.h"
//-------------------------------------------//
class RedBlade : public Blade
{
public:
	RedBlade(const sf::Vector2f& Position);
	virtual void Move() override;
	virtual void Collided(const BaseGameObject& GivenCollidedObject) override;
private:
	void SetLeftCharging();
	void SetRightCharging();
	void ChargingEffect();
private:
	sf::Clock m_ChargingClock;
	bool m_Charge = false;
	bool m_ChangeDefaultChargingSides = false;

	// Define x verible and y verible that will hold the XScale value each time and will be decreased
	// as well the y verible in order to get the dashing effect
	float m_x = 0.35f, m_y = 0.35f;

	// For scaling the 200x200 object sprite
	float m_XScale = 0.35f;
	float m_YScale = 0.35f;

	float m_LeftChargingSpeed = -20.0;
	float m_RightChargingSpeed = 20.0;
	bool m_LeftCharging = true;
	bool m_RightCharging = false;
};
//-------------------------------------------//