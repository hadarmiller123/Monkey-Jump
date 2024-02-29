#pragma once
//-------------------------------------------//
#include "StaticObject.h"
#include "Floor.h"
#include "Resources.h"
#include "Factory.h"
//-------------------------------------------//
class StaticBouncingFloor : public StaticObject, public Floor
{
public:
	StaticBouncingFloor(const sf::Vector2f& Position);
	virtual void Draw(sf::RenderWindow& GivenScreen) override;
	// If a collision with monkey happend true is set to m_IsBouncing
	void SetBouncingStatus();
private:
	bool m_IsBouncing = false;
};
//-------------------------------------------//