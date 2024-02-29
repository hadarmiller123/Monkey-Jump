#pragma once
//-------------------------------------------//
#include "StaticObject.h"
#include "Floor.h"
#include "Resources.h"
//-------------------------------------------//
class StaticCloudFloor : public StaticObject, public Floor
{
public:
	StaticCloudFloor(const sf::Vector2f& Position);
private:

};
//-------------------------------------------//