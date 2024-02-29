#include "CollisionHandling.h"
#include "Monkey.h"
#include "Blade.h"
#include "BlackBlade.h"
#include "RedBlade.h"
#include "Invisible.h"
#include "Floor.h"
#include "MovingFloor.h"
#include "StaticNormalFloor.h"
#include "StaticInvisibleFloor.h"
#include "StaticBouncingFloor.h"
#include "StaticCloudFloor.h"
#include "MovingNormalFloor.h"
#include "MovingInvisibleFloor.h"
#include "MovingBouncingFloor.h"
#include "MovingCloudFloor.h"
#include "FinishLine.h"
//-----------------------------------------------//
// All dynamic casting that apperes in this code page is due to the reason that 
// in virtual multiple inheritance situation casting in
// compile time is impossible, the compiler doesent know the currect offset that should be point
// on the wanted object in the memory
//-----------------------------------------------//
//---------------Monkey Collision----------------//
//-----------------------------------------------//
//----------------------------------Monkey - Blades----------------------------------//
void MonkeyBlade(BaseGameObject& GivenMonkey, BaseGameObject& GivenBlade) 
{
	// If the monkey is invisible we wont make any changes but if he doesent we set him to be disposed
	if (!dynamic_cast<Monkey&>(GivenMonkey).GetInvisibilityStatus()) {
		GivenMonkey.SetDisposedStatus();
	}
}
//-----------------------------------------------//
void MonkeyBlackBlade(BaseGameObject& GivenMonkey, BaseGameObject& GivenBlackBlade) 
{
	MonkeyBlade(GivenMonkey, GivenBlackBlade);
}
//-----------------------------------------------//
void MonkeyRedBlade(BaseGameObject& GivenMonkey, BaseGameObject& GivenRedBlade) 
{
	MonkeyBlade(GivenMonkey, GivenRedBlade);
}
//-----------------------------------------------//
//----------------------------------Monkey - Floors----------------------------------//
bool MonkeyFloor(BaseGameObject& GivenMonkey, BaseGameObject& GivenFloor) // General function for monkey floor collision
{
	if (dynamic_cast<Floor&>(GivenFloor).GetVisibleStatus()){
		dynamic_cast<Monkey&>(GivenMonkey).SetJumpStatus(dynamic_cast<Floor&>(GivenFloor).GetGravity());
		return true; // return true if a floor has been collided with the monkey and he was higher
	}
	return false;
}
//-----------------------------------------------//
void MonkeyStaticNormalFloor(BaseGameObject& GivenMonkey, BaseGameObject& GivenStaticNormalFloor) 
{
	MonkeyFloor(GivenMonkey, GivenStaticNormalFloor);
}
//-----------------------------------------------//
void MonkeyStaticInvisibleFloor(BaseGameObject& GivenMonkey, BaseGameObject& GivenStaticInvisibleFloor)
{
	MonkeyFloor(GivenMonkey, GivenStaticInvisibleFloor);
}
//-----------------------------------------------//
void MonkeyStaticBouncingFloor(BaseGameObject& GivenMonkey, BaseGameObject& GivenStaticBouncingFloor) 
{
	// getting the status of which a bounce happend for the animation of the bounce effect*/
	if (MonkeyFloor(GivenMonkey, GivenStaticBouncingFloor)) {
		dynamic_cast<StaticBouncingFloor&>(GivenStaticBouncingFloor).SetBouncingStatus();
	}
}
//-----------------------------------------------//
void MonkeyStaticCloudFloor(BaseGameObject& GivenMonkey, BaseGameObject& GivenStaticCloudFloor) 
{
	// Cloud floor as the fanctionality of dispose after bounced on it once
	if (MonkeyFloor(GivenMonkey, GivenStaticCloudFloor)) {
		GivenStaticCloudFloor.SetDisposedStatus();
	}
}
//-----------------------------------------------//
void MonkeyMovingNormalFloor(BaseGameObject& GivenMonkey, BaseGameObject& GivenMovingNormalFloor) 
{
	MonkeyFloor(GivenMonkey, GivenMovingNormalFloor);
}
//-----------------------------------------------//
void MonkeyMovingInvisibleFloor(BaseGameObject& GivenMonkey, BaseGameObject& GivenMovingInvisibleFloor)
{
	MonkeyFloor(GivenMonkey, GivenMovingInvisibleFloor);
}
//-----------------------------------------------//
void MonkeyMovingBouncingFloor(BaseGameObject& GivenMonkey, BaseGameObject& GivenMovingBouncingFloor) 
{
	// getting the status of which a bounce happend for the animation of the bounce effect
	if (MonkeyFloor(GivenMonkey, GivenMovingBouncingFloor)) {
		dynamic_cast<MovingBouncingFloor&>(GivenMovingBouncingFloor).SetBouncingStatus();
	}
}
//-----------------------------------------------//
void MonkeyMovingCloudFloor(BaseGameObject& GivenMonkey, BaseGameObject& GivenMovingCloudFloor) 
{
	// Cloud floor as the fanctionality of dispose after bounced on it once
	if (MonkeyFloor(GivenMonkey, GivenMovingCloudFloor)) {
		GivenMovingCloudFloor.SetDisposedStatus();
	}
}
//-----------------------------------------------//
//----------------------------------Monkey - Invisible----------------------------------//
void MonkeyInvisible(BaseGameObject& GivenMonkey, BaseGameObject& GivenInvisible)
{
	dynamic_cast<Invisible&>(GivenInvisible).SetDisposedStatus();
	dynamic_cast<Monkey&>(GivenMonkey).SetInvisibilityStatus(dynamic_cast<Invisible&>(GivenInvisible));
}
//-----------------------------------------------//
//----------------------------------Monkey - Finish Line----------------------------------//
void MonkeyFinishLine(BaseGameObject& GivenMonkey, BaseGameObject& GivenFinishLine) 
{
	dynamic_cast<Monkey&>(GivenMonkey).SetFinishStatus(dynamic_cast<FinishLine&>(GivenFinishLine));
}
//-----------------------------------------------//
//--------------Blades Collision-----------------//
//-----------------------------------------------//
//----------------------------------Blades - Floors----------------------------------//
void BladeFloor(BaseGameObject& GivenBlade, BaseGameObject& GivenFloor)
{
	dynamic_cast<Blade&>(GivenBlade).Collided(GivenFloor);
}
//-----------------------------------------------//
void BlackBladeStaticNormalFloor(BaseGameObject& GivenBlackBlade, BaseGameObject& GivenStaticNormalFloor)
{
	BladeFloor(GivenBlackBlade, GivenStaticNormalFloor);
}
//-----------------------------------------------//
void RedBladeStaticNormalFloor(BaseGameObject& GivenRedBlade, BaseGameObject& GivenStaticNormalFloor)
{
	BladeFloor(GivenRedBlade, GivenStaticNormalFloor);
}
//-----------------------------------------------//
void BlackBladeStaticInvisibleFloor(BaseGameObject& GivenBlackBlade, BaseGameObject& GivenStaticInvisibleFloor)
{
	BladeFloor(GivenBlackBlade, GivenStaticInvisibleFloor);
}
//-----------------------------------------------//
void RedBladeStaticInvisibleFloor(BaseGameObject& GivenRedBlade, BaseGameObject& GivenStaticInvisibleFloor)
{
	BladeFloor(GivenRedBlade, GivenStaticInvisibleFloor);
}
//-----------------------------------------------//
void BlackBladeStaticBouncingFloor(BaseGameObject& GivenBlackBlade, BaseGameObject& GivenStaticBouncingFloor)
{
	BladeFloor(GivenBlackBlade, GivenStaticBouncingFloor);
}
//-----------------------------------------------//
void RedBladeStaticBouncingFloor(BaseGameObject& GivenRedBlade, BaseGameObject& GivenStaticBouncingFloor)
{
	BladeFloor(GivenRedBlade, GivenStaticBouncingFloor);
}
//-----------------------------------------------//
void BlackBladeStaticCloudFloor(BaseGameObject& GivenBlackBlade, BaseGameObject& GivenStaticCloudFloor)
{
	BladeFloor(GivenBlackBlade, GivenStaticCloudFloor);
}
//-----------------------------------------------//
void RedBladeStaticCloudFloor(BaseGameObject& GivenRedBlade, BaseGameObject& GivenStaticCloudFloor)
{
	BladeFloor(GivenRedBlade, GivenStaticCloudFloor);
}
//-----------------------------------------------//
void BlackBladeMovingNormalFloor(BaseGameObject& GivenBlackBlade, BaseGameObject& GivenMovingNormalFloor)
{
	BladeFloor(GivenBlackBlade, GivenMovingNormalFloor);
}
//-----------------------------------------------//
void RedBladeMovingNormalFloor(BaseGameObject& GivenRedBlade, BaseGameObject& GivenMovingNormalFloor)
{
	BladeFloor(GivenRedBlade, GivenMovingNormalFloor);
}
//-----------------------------------------------//
void BlackBladeMovingInvisibleFloor(BaseGameObject& GivenBlackBlade, BaseGameObject& GivenMovingInvisibleFloor)
{
	BladeFloor(GivenBlackBlade, GivenMovingInvisibleFloor);
}
//-----------------------------------------------//
void RedBladeMovingInvisibleFloor(BaseGameObject& GivenRedBlade, BaseGameObject& GivenMovingInvisibleFloor)
{
	BladeFloor(GivenRedBlade, GivenMovingInvisibleFloor);
}
//-----------------------------------------------//
void BlackBladeMovingBouncingFloor(BaseGameObject& GivenBlackBlade, BaseGameObject& GivenMovingBouncingFloor)
{
	BladeFloor(GivenBlackBlade, GivenMovingBouncingFloor);
}
//-----------------------------------------------//
void RedBladeMovingBouncingFloor(BaseGameObject& GivenRedBlade, BaseGameObject& GivenMovingBouncingFloor)
{
	BladeFloor(GivenRedBlade, GivenMovingBouncingFloor);
}
//-----------------------------------------------//
void BlackBladeMovingCloudFloor(BaseGameObject& GivenBlackBlade, BaseGameObject& GivenMovingCloudFloor)
{
	BladeFloor(GivenBlackBlade, GivenMovingCloudFloor);
}
//-----------------------------------------------//
void RedBladeMovingCloudFloor(BaseGameObject& GivenRedBlade, BaseGameObject& GivenMovingCloudFloor)
{
	BladeFloor(GivenRedBlade, GivenMovingCloudFloor);
}
//-----------------------------------------------//
//----------------------------------Blades - Invisible----------------------------------//
void BladeInvisible(BaseGameObject& GivenBlade, BaseGameObject& GivenInvisible)
{
	dynamic_cast<Blade&>(GivenBlade).Collided(GivenInvisible);
}
//-----------------------------------------------//
void BlackBladeInvisible(BaseGameObject& GivenBlackBlade, BaseGameObject& GivenInvisible)
{
	BladeInvisible(GivenBlackBlade, GivenInvisible);
}
//-----------------------------------------------//
void RedBladeInvisible(BaseGameObject& GivenRedBlade, BaseGameObject& GivenInvisible)
{
	BladeInvisible(GivenRedBlade, GivenInvisible);
}
//-----------------------------------------------//
//----------Moving Floors collision--------------//
//-----------------------------------------------//
//----------------------------------Moving Floors - Blades----------------------------------//
void MovingFloorBlade(BaseGameObject& GivenMovingFloor, BaseGameObject& GivenBlade)
{
	dynamic_cast<MovingFloor&>(GivenMovingFloor).Collided(GivenBlade);
}
//-----------------------------------------------//
void MovingNormalFloorBlackBlade(BaseGameObject& GivenMovingNormalFloor, BaseGameObject& GivenBlackBlade)
{
	MovingFloorBlade(GivenMovingNormalFloor, GivenBlackBlade);
}
//-----------------------------------------------//
void MovingNormalFloorRedBlade(BaseGameObject& GivenMovingNormalFloor, BaseGameObject& GivenRedBlade)
{
	MovingFloorBlade(GivenMovingNormalFloor, GivenRedBlade);
}
//-----------------------------------------------//
void MovingInvisibleFloorBlackBlade(BaseGameObject& GivenMovingInvisibleFloor, BaseGameObject& GivenBlackBlade)
{
	MovingFloorBlade(GivenMovingInvisibleFloor, GivenBlackBlade);
}
//-----------------------------------------------//
void MovingInvisibleFloorRedBlade(BaseGameObject& GivenMovingInvisibleFloor, BaseGameObject& GivenRedBlade)
{
	MovingFloorBlade(GivenMovingInvisibleFloor, GivenRedBlade);
}
//-----------------------------------------------//
void MovingBouncingFloorBlackBlade(BaseGameObject& GivenMovingBouncingFloor, BaseGameObject& GivenBlackBlade)
{
	MovingFloorBlade(GivenMovingBouncingFloor, GivenBlackBlade);
}
//-----------------------------------------------//
void MovingBouncingFloorRedBlade(BaseGameObject& GivenMovingBouncingFloor, BaseGameObject& GivenRedBlade)
{
	MovingFloorBlade(GivenMovingBouncingFloor, GivenRedBlade);
}
//-----------------------------------------------//
void MovingCloudFloorBlackBlade(BaseGameObject& GivenMovingCloudFloor, BaseGameObject& GivenBlackBlade)
{
	MovingFloorBlade(GivenMovingCloudFloor, GivenBlackBlade);
}
//-----------------------------------------------//
void MovingCloudFloorRedBlade(BaseGameObject& GivenMovingCloudFloor, BaseGameObject& GivenRedBlade)
{
	MovingFloorBlade(GivenMovingCloudFloor, GivenRedBlade);
}
//-----------------------------------------------//
//----------------------------------Moving Floors - Invisible----------------------------------//
void MovingFloorInvisible(BaseGameObject& GivenMovingFloor, BaseGameObject& GivenInvisible)
{
	dynamic_cast<MovingFloor&>(GivenMovingFloor).Collided(GivenInvisible);
}
//-----------------------------------------------//
void MovingNormalFloorInvisible(BaseGameObject& GivenMovingNormalFloor, BaseGameObject& GivenInvisible)
{
	MovingFloorInvisible(GivenMovingNormalFloor, GivenInvisible);
}
//-----------------------------------------------//
void MovingInvisibleFloorInvisible(BaseGameObject& GivenMovingInvisibleFloor, BaseGameObject& GivenInvisible)
{
	MovingFloorInvisible(GivenMovingInvisibleFloor, GivenInvisible);
}
//-----------------------------------------------//
void MovingBouncingFloorInvisible(BaseGameObject& GivenMovingBouncingFloor, BaseGameObject& GivenInvisible)
{
	MovingFloorInvisible(GivenMovingBouncingFloor, GivenInvisible);
}
//-----------------------------------------------//
void MovingCloudFloorInvisible(BaseGameObject& GivenMovingCloudFloor, BaseGameObject& GivenInvisible)
{
	MovingFloorInvisible(GivenMovingCloudFloor, GivenInvisible);
}
//-----------------------------------------------//
//----------------------------------Moving Floors - Moving Floors----------------------------------//
void MovingFloorMovingFloor(BaseGameObject& GivenMovingFloor1, BaseGameObject& GivenMovingFloor2)
{
	// Calling both floors collided function
	dynamic_cast<MovingFloor&>(GivenMovingFloor1).Collided(GivenMovingFloor2);
	dynamic_cast<MovingFloor&>(GivenMovingFloor2).Collided(GivenMovingFloor1);
}
//-----------------------------------------------//
void MovingNormalFloorMovingNormalFloor(BaseGameObject& GivenMovingNormalFloor1, BaseGameObject& GivenMovingNormalFloor2)
{
	MovingFloorMovingFloor(GivenMovingNormalFloor1, GivenMovingNormalFloor2);
}
//-----------------------------------------------//
void MovingNormalFloorMovingInvisibleFloor(BaseGameObject& GivenMovingNormalFloor, BaseGameObject& GivenMovingInvisibleFloor)
{
	MovingFloorMovingFloor(GivenMovingNormalFloor, GivenMovingInvisibleFloor);
}
//-----------------------------------------------//
void MovingNormalFloorMovingBouncingFloor(BaseGameObject& GivenMovingNormalFloor, BaseGameObject& GivenMovingBouncingFloor)
{
	MovingFloorMovingFloor(GivenMovingNormalFloor, GivenMovingBouncingFloor);
}
//-----------------------------------------------//
void MovingNormalFloorMovingCloudFloor(BaseGameObject& GivenMovingNormalFloor, BaseGameObject& GivenMovingCloudFloor)
{
	MovingFloorMovingFloor(GivenMovingNormalFloor, GivenMovingCloudFloor);
}
//-----------------------------------------------//
void MovingInvisibleFloorMovingNormalFloor(BaseGameObject& GivenMovingInvisibleFloor, BaseGameObject& GivenMovingNormalFloor)
{
	MovingFloorMovingFloor(GivenMovingInvisibleFloor, GivenMovingNormalFloor);
}
//-----------------------------------------------//
void MovingInvisibleFloorMovingInvisibleFloor(BaseGameObject& GivenMovingInvisibleFloor1, BaseGameObject& GivenMovingInvisibleFloor2)
{
	MovingFloorMovingFloor(GivenMovingInvisibleFloor1, GivenMovingInvisibleFloor2);
}
//-----------------------------------------------//
void MovingInvisibleFloorMovingBouncingFloor(BaseGameObject& GivenMovingInvisibleFloor, BaseGameObject& GivenMovingBouncingFloor)
{
	MovingFloorMovingFloor(GivenMovingInvisibleFloor, GivenMovingBouncingFloor);
}
//-----------------------------------------------//
void MovingInvisibleFloorMovingCloudFloor(BaseGameObject& GivenMovingInvisibleFloor, BaseGameObject& GivenMovingCloudFloor)
{
	MovingFloorMovingFloor(GivenMovingInvisibleFloor, GivenMovingCloudFloor);
}
//-----------------------------------------------//
void MovingBouncingFloorMovingNormalFloor(BaseGameObject& GivenMovingBouncingFloor, BaseGameObject& GivenMovingNormalFloor)
{
	MovingFloorMovingFloor(GivenMovingBouncingFloor, GivenMovingNormalFloor);
}
//-----------------------------------------------//
void MovingBouncingFloorMovingInvisibleFloor(BaseGameObject& GivenMovingBouncingFloor, BaseGameObject& GivenMovingInvisibleFloor)
{
	MovingFloorMovingFloor(GivenMovingBouncingFloor, GivenMovingInvisibleFloor);
}
//-----------------------------------------------//
void MovingBouncingFloorMovingBouncingFloor(BaseGameObject& GivenMovingBouncingFloor1, BaseGameObject& GivenMovingBouncingFloor2)
{
	MovingFloorMovingFloor(GivenMovingBouncingFloor1, GivenMovingBouncingFloor2);
}
//-----------------------------------------------//
void MovingBouncingFloorMovingCloudFloor(BaseGameObject& GivenMovingBouncingFloor, BaseGameObject& GivenMovingCloudFloor)
{
	MovingFloorMovingFloor(GivenMovingBouncingFloor, GivenMovingCloudFloor);
}
//-----------------------------------------------//
void MovingCloudFloorMovingNormalFloor(BaseGameObject& GivenMovingCloudFloor, BaseGameObject& GivenMovingNormalFloor)
{
	MovingFloorMovingFloor(GivenMovingCloudFloor, GivenMovingNormalFloor);
}
//-----------------------------------------------//
void MovingCloudFloorMovingInvisibleFloor(BaseGameObject& GivenMovingCloudFloor, BaseGameObject& GivenMovingInvisibleFloor)
{
	MovingFloorMovingFloor(GivenMovingCloudFloor, GivenMovingInvisibleFloor);
}
//-----------------------------------------------//
void MovingCloudFloorMovingBouncingFloor(BaseGameObject& GivenMovingCloudFloor, BaseGameObject& GivenMovingBouncingFloor)
{
	MovingFloorMovingFloor(GivenMovingCloudFloor, GivenMovingBouncingFloor);
}
//-----------------------------------------------//
void MovingCloudFloorMovingCloudFloor(BaseGameObject& GivenMovingCloudFloor1, BaseGameObject& GivenMovingCloudFloor2)
{
	MovingFloorMovingFloor(GivenMovingCloudFloor1, GivenMovingCloudFloor2);
}
//-----------------------------------------------//
//-----------------------------------------------//
//-----------------------------------------------//
using HitFunctionPtr = void (*)(BaseGameObject&, BaseGameObject& );

using Key = std::pair<std::type_index, std::type_index>;

using HitMap = std::map<Key, HitFunctionPtr>;
//-----------------------------------------------//
HitMap InitializeCollisionMap()
{
	HitMap hm;
	// Monkey collision with blades
	hm[Key(typeid(Monkey), typeid(BlackBlade))] = &MonkeyBlackBlade;
	hm[Key(typeid(Monkey), typeid(RedBlade))] = &MonkeyRedBlade;

	// Monkey collision with floors
	hm[Key(typeid(Monkey), typeid(StaticNormalFloor))] = &MonkeyStaticNormalFloor;
	hm[Key(typeid(Monkey), typeid(StaticInvisibleFloor))] = &MonkeyStaticInvisibleFloor;
	hm[Key(typeid(Monkey), typeid(StaticBouncingFloor))] = &MonkeyStaticBouncingFloor;
	hm[Key(typeid(Monkey), typeid(StaticCloudFloor))] = &MonkeyStaticCloudFloor;

	hm[Key(typeid(Monkey), typeid(MovingNormalFloor))] = &MonkeyMovingNormalFloor;
	hm[Key(typeid(Monkey), typeid(MovingInvisibleFloor))] = &MonkeyMovingInvisibleFloor;
	hm[Key(typeid(Monkey), typeid(MovingBouncingFloor))] = &MonkeyMovingBouncingFloor;
	hm[Key(typeid(Monkey), typeid(MovingCloudFloor))] = &MonkeyMovingCloudFloor;

	// Monkey collision with invisible
	hm[Key(typeid(Monkey), typeid(Invisible))] = &MonkeyInvisible;

	// Monkey collision with Finish line
	hm[Key(typeid(Monkey), typeid(FinishLine))] = &MonkeyFinishLine;

	// Blades collision with floors
	hm[Key(typeid(BlackBlade), typeid(StaticNormalFloor))] = &BlackBladeStaticNormalFloor;
	hm[Key(typeid(RedBlade), typeid(StaticNormalFloor))] = &RedBladeStaticNormalFloor;

	hm[Key(typeid(BlackBlade), typeid(StaticInvisibleFloor))] = &BlackBladeStaticInvisibleFloor;
	hm[Key(typeid(RedBlade), typeid(StaticInvisibleFloor))] = &RedBladeStaticInvisibleFloor;

	hm[Key(typeid(BlackBlade), typeid(StaticBouncingFloor))] = &BlackBladeStaticBouncingFloor;
	hm[Key(typeid(RedBlade), typeid(StaticBouncingFloor))] = &RedBladeStaticBouncingFloor;

	hm[Key(typeid(BlackBlade), typeid(StaticCloudFloor))] = &BlackBladeStaticCloudFloor;
	hm[Key(typeid(RedBlade), typeid(StaticCloudFloor))] = &RedBladeStaticCloudFloor;

	hm[Key(typeid(BlackBlade), typeid(MovingNormalFloor))] = &BlackBladeMovingNormalFloor;
	hm[Key(typeid(RedBlade), typeid(MovingNormalFloor))] = &RedBladeMovingNormalFloor;

	hm[Key(typeid(BlackBlade), typeid(MovingInvisibleFloor))] = &BlackBladeMovingInvisibleFloor;
	hm[Key(typeid(RedBlade), typeid(MovingInvisibleFloor))] = &RedBladeMovingInvisibleFloor;

	hm[Key(typeid(BlackBlade), typeid(MovingBouncingFloor))] = &BlackBladeMovingBouncingFloor;
	hm[Key(typeid(RedBlade), typeid(MovingBouncingFloor))] = &RedBladeMovingBouncingFloor;

	hm[Key(typeid(BlackBlade), typeid(MovingCloudFloor))] = &BlackBladeMovingCloudFloor;
	hm[Key(typeid(RedBlade), typeid(MovingCloudFloor))] = &RedBladeMovingCloudFloor;

	// Blades collision with invisible
	hm[Key(typeid(BlackBlade), typeid(Invisible))] = &BlackBladeInvisible;
	hm[Key(typeid(RedBlade), typeid(Invisible))] = &RedBladeInvisible;

	// Moving Floors collision with Blades
	hm[Key(typeid(MovingNormalFloor), typeid(BlackBlade))] = &MovingNormalFloorBlackBlade;
	hm[Key(typeid(MovingNormalFloor), typeid(RedBlade))] = &MovingNormalFloorRedBlade;

	hm[Key(typeid(MovingInvisibleFloor), typeid(BlackBlade))] = &MovingInvisibleFloorBlackBlade;
	hm[Key(typeid(MovingInvisibleFloor), typeid(RedBlade))] = &MovingInvisibleFloorRedBlade;

	hm[Key(typeid(MovingBouncingFloor), typeid(BlackBlade))] = &MovingBouncingFloorBlackBlade;
	hm[Key(typeid(MovingBouncingFloor), typeid(RedBlade))] = &MovingBouncingFloorRedBlade;

	hm[Key(typeid(MovingCloudFloor), typeid(BlackBlade))] = &MovingCloudFloorBlackBlade;
	hm[Key(typeid(MovingCloudFloor), typeid(RedBlade))] = &MovingCloudFloorRedBlade;

	// Moving Floors collision with invisible
	hm[Key(typeid(MovingNormalFloor), typeid(Invisible))] = &MovingNormalFloorInvisible;
	hm[Key(typeid(MovingInvisibleFloor), typeid(Invisible))] = &MovingInvisibleFloorInvisible;
	hm[Key(typeid(MovingBouncingFloor), typeid(Invisible))] = &MovingBouncingFloorInvisible;
	hm[Key(typeid(MovingCloudFloor), typeid(Invisible))] = &MovingCloudFloorInvisible;

	// Moving Floors collision with moving floors
	hm[Key(typeid(MovingNormalFloor), typeid(MovingNormalFloor))] = &MovingNormalFloorMovingNormalFloor;
	hm[Key(typeid(MovingNormalFloor), typeid(MovingInvisibleFloor))] = &MovingNormalFloorMovingInvisibleFloor;
	hm[Key(typeid(MovingNormalFloor), typeid(MovingBouncingFloor))] = &MovingNormalFloorMovingBouncingFloor;
	hm[Key(typeid(MovingNormalFloor), typeid(MovingCloudFloor))] = &MovingNormalFloorMovingCloudFloor;

	hm[Key(typeid(MovingInvisibleFloor), typeid(MovingNormalFloor))] = &MovingInvisibleFloorMovingNormalFloor;
	hm[Key(typeid(MovingInvisibleFloor), typeid(MovingInvisibleFloor))] = &MovingInvisibleFloorMovingInvisibleFloor;
	hm[Key(typeid(MovingInvisibleFloor), typeid(MovingBouncingFloor))] = &MovingInvisibleFloorMovingBouncingFloor;
	hm[Key(typeid(MovingInvisibleFloor), typeid(MovingCloudFloor))] = &MovingInvisibleFloorMovingCloudFloor;

	hm[Key(typeid(MovingBouncingFloor), typeid(MovingNormalFloor))] = &MovingBouncingFloorMovingNormalFloor;
	hm[Key(typeid(MovingBouncingFloor), typeid(MovingInvisibleFloor))] = &MovingBouncingFloorMovingInvisibleFloor;
	hm[Key(typeid(MovingBouncingFloor), typeid(MovingBouncingFloor))] = &MovingBouncingFloorMovingBouncingFloor;
	hm[Key(typeid(MovingBouncingFloor), typeid(MovingCloudFloor))] = &MovingBouncingFloorMovingCloudFloor;

	hm[Key(typeid(MovingCloudFloor), typeid(MovingNormalFloor))] = &MovingCloudFloorMovingNormalFloor;
	hm[Key(typeid(MovingCloudFloor), typeid(MovingInvisibleFloor))] = &MovingCloudFloorMovingInvisibleFloor;
	hm[Key(typeid(MovingCloudFloor), typeid(MovingBouncingFloor))] = &MovingCloudFloorMovingBouncingFloor;
	hm[Key(typeid(MovingCloudFloor), typeid(MovingCloudFloor))] = &MovingCloudFloorMovingCloudFloor;

	return hm;
}
//-----------------------------------------------//
HitFunctionPtr SearchFunction(const std::type_index& FirstClass, const std::type_index& SecondClass)
{	
	static HitMap CollisionFunctionsMap = InitializeCollisionMap();
	auto CollisionMapObject = CollisionFunctionsMap.find(std::make_pair(FirstClass, SecondClass));
	if (CollisionMapObject == CollisionFunctionsMap.end()) {
		return nullptr;
	}

	return CollisionMapObject->second;
}
//-----------------------------------------------//
void ProccessCollision(BaseGameObject& FirstObject, BaseGameObject& SecondObject)
{
	auto CollisionFunction = SearchFunction(typeid(FirstObject), typeid(SecondObject));
	if (CollisionFunction == nullptr) {
		return;
	}

	CollisionFunction(FirstObject, SecondObject);
}
//-----------------------------------------------//