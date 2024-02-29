#include "Floor.h"
//-------------------------------------------//
Floor::Floor() {}
//-------------------------------------------//
void Floor::UpdateMyVisibilityStatus(const Monkey& GivenMonkey)
{
	// If the monkey sprite above the floor sprite we change the visibility of the floor
	// such as the monkey could land on it
	if (GivenMonkey.GetObjectSprite().getGlobalBounds().top + GivenMonkey.GetObjectSprite().getGlobalBounds().height <=
		GetObjectSprite().getGlobalBounds().top) {
		if (m_Visible != true) {
			m_Visible = true;
		}
	}
	// If the monkey sprite not fully above the floor he just can go through the floor from down
	else {
		if (GetVisibleStatus() != false) {
			m_Visible = false;
		}
	}
}
//-------------------------------------------//
bool Floor::GetVisibleStatus() const
{
	return m_Visible;
}
//-------------------------------------------//
float Floor::GetGravity() const
{
	return m_Gravity;
}
//-------------------------------------------//