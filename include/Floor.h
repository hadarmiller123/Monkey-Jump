#pragma once
//-------------------------------------------//
#include "Monkey.h"
#include "BaseGameObject.h"
//-------------------------------------------//
class Floor : virtual public BaseGameObject
{
public:
	Floor();

	// Update the visibility status according to the monkey position
	// this function can only be called if a monkey object calls it and sent it himself
	// virtual beacuse each floor can define his way of updating the visibility
	// for example unvisible floors can be visible only when monkey in invisible mod
	virtual void UpdateMyVisibilityStatus(const Monkey& GivenMonkey);
	bool GetVisibleStatus() const;
	float GetGravity() const;
protected:
	// Default gravity
	float m_Gravity = 0.0f;

	// True = defualt Visiavility until moving accures
	bool m_Visible = true;
private:
};