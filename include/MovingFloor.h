#pragma once
//-------------------------------------------//
#include "MovingObject.h"
#include "Floor.h"
#include "Resources.h"
//-------------------------------------------//
//Intermediate class for only making the collide virtual function possible to moving floors
// the reason behind it is that in class floor there is no option to define collided function
// beacuse there is combination of static floors that cant move, thats why its wrong to define for
// them unnessacery functionality, only the moving floors can make a collision since they can move
class MovingFloor : public MovingObject, public Floor
{
public:
	// Every floor must define a collided function in order to make an assemptions
	// whether the movement should be changed or the speed or some other functionality
	virtual void Collided(const BaseGameObject& GivenCollidedObject) = 0;
private:

};
//-------------------------------------------//