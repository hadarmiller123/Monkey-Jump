#include "MovingObject.h"
//-------------------------------------------//
bool MovingObject::IsCollide(const MovingObject& GivenMovingObject) const
{
	// Returning false when object are checking if he collide with himself
	if (&*this == &GivenMovingObject) {
		return false;
	}

	if (m_ObjectSprite.getGlobalBounds().intersects(GivenMovingObject.GetObjectSprite().getGlobalBounds())) {
		return true;
	}

	return false;
}
//-------------------------------------------//
bool MovingObject::IsCollide(const StaticObject& GivenStaticObject) const
{
	if (m_ObjectSprite.getGlobalBounds().intersects(GivenStaticObject.GetObjectSprite().getGlobalBounds())) {
		return true;
	}

	return false;
}
//-------------------------------------------//