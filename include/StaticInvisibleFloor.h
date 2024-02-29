#pragma once
//-------------------------------------------//
#include "StaticObject.h"
#include "Floor.h"
#include "Resources.h"
//-------------------------------------------//
class StaticInvisibleFloor : public StaticObject, public Floor
{
public:
	StaticInvisibleFloor(const sf::Vector2f& Position);
	virtual void UpdateMyVisibilityStatus(const Monkey& GivenMonkey) override;
private:

};
//-------------------------------------------//