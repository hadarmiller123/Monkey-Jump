#pragma once
//-------------------------------------------//
#include "MovingObject.h"
#include "Resources.h"
//-------------------------------------------//
const float ROTATE_MOVEMENT = 20.0f;
//-------------------------------------------//
class Blade : public MovingObject
{
public:
	Blade();
	virtual void Move() = 0;

	// Each type of blade that inherited from blade base object must override Collided function
	// that could update his status of moving functionality and other functionalities
	virtual void Collided(const BaseGameObject& GivenCollidedObject) = 0;
protected:
	float m_DiagonalLine = 0;
private:
	
};
//-------------------------------------------//