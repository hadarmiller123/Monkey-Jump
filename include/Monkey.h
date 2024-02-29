#pragma once
//-------------------------------------------//
#include "MovingObject.h"
#include "Invisible.h"
#include "Floor.h"
#include "FinishLine.h"
#include "Resources.h"
#include "Factory.h"
//-------------------------------------------//
const float SIDE_MOVEMENT = 10.0f;
//-------------------------------------------//
class Monkey : public MovingObject
{
public:
	Monkey(const sf::Vector2f& Position);

	virtual void Move();

	// Only Invisible object can be changing the visibility status
	void SetInvisibilityStatus(const Invisible& InvisibleType);
	bool GetInvisibilityStatus() const;

	// Setting the jump status will resualt the monkey to jump in the gravity that sented to him as a GivenGravity parameter
	void SetJumpStatus(const float& GivenGravity);
	bool GetJumpStatus() const;
	void SetFinishStatus(const FinishLine& GivenFinishLine);
	bool GetFinishedStatus() const;
private:
	void InvisibleEffect();
private:
	sf::Clock m_InvisibleClock;
	bool m_Jump = false;
	bool m_Invisible = false;
	bool m_InvisibleClockRestart = false;
	bool m_UpperForceActivated = false;
	float m_Gravity = 0.0f;
	bool m_Finished = false;

	sf::Vector2f MonkeyNewPosition;
	bool m_IsMonkeyNewPositionReset = false;
};