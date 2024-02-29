#pragma once
//-------------------------------------------//
#include "StaticObject.h"
#include "Floor.h"
#include "Resources.h"
#include "Factory.h"
//-------------------------------------------//
class StaticNormalFloor : public StaticObject, public Floor
{
public:
	StaticNormalFloor(const sf::Vector2f& Position);
private:

};
//-------------------------------------------//