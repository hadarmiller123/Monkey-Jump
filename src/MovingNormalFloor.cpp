#include "MovingNormalFloor.h"
//-------------------------------------------//
static auto registerIt = Factory<MovingObject>::instance().registerType(
	ObjectType::MovingNormalFloorSymbol,
	[](sf::Vector2f position) -> std::unique_ptr<MovingObject>
	{
		return std::make_unique<MovingNormalFloor>(position);
	}
);
//-------------------------------------------//
MovingNormalFloor::MovingNormalFloor(const sf::Vector2f& Position)
{
	SetNewSpritePosition(Position);

	m_ObjectSprite.setTexture(Resources::Instance().GetNormalFloorTexture(*this));
	m_ObjectSprite.setOrigin(sf::Vector2f(m_ObjectSprite.getGlobalBounds().width / 2,
		m_ObjectSprite.getGlobalBounds().height));// setting the origin to the bottom middle

	// Initializes gravity to normal floor gravity
	m_Gravity = -14.0f;
}
//-------------------------------------------//
void MovingNormalFloor::Move()
{
	if (m_LeftMovement) {
		if (m_ObjectSprite.getPosition().x - m_ObjectSprite.getGlobalBounds().width / 2 < 0.0f) {
			m_LeftMovement = false;
			m_RightMovement = true;
		}
		SetNewSpritePosition(sf::Vector2f(m_ObjectSprite.getPosition().x + m_LeftMovementSpeed, m_ObjectSprite.getPosition().y));
	}
	else if (m_RightMovement) {
		if (m_ObjectSprite.getPosition().x + m_ObjectSprite.getGlobalBounds().width / 2 > float(SCREEN_WIDTH)) {
			m_RightMovement = false;
			m_LeftMovement = true;
		}
		SetNewSpritePosition(sf::Vector2f(m_ObjectSprite.getPosition().x + m_RightMovementSpeed, m_ObjectSprite.getPosition().y));
	}
}
//-------------------------------------------//
void MovingNormalFloor::Collided(const BaseGameObject& GivenCollidedObject)
{
	// If the blade collided with base object from the left
	// we set his movement to right
	if (m_ObjectSprite.getPosition().x <
		GivenCollidedObject.GetObjectSprite().getPosition().x) {

		// Setting the blade position to the object position decreased by the floor width
		SetLeftMovement();
		// Setting the floor position to the object position - his width/2 - the *this object width/2
		SetNewSpritePosition(sf::Vector2f(GivenCollidedObject.GetObjectSprite().getPosition().x -
			GivenCollidedObject.GetObjectSprite().getGlobalBounds().width / 2 -
			m_ObjectSprite.getGlobalBounds().width / 2, GetObjectSprite().getPosition().y));
	}
	// The opposite
	else {
		SetRightMovement();

		// Setting the floor position to the object position + his width/2 + the *this object width/2
		SetNewSpritePosition(sf::Vector2f(GivenCollidedObject.GetObjectSprite().getPosition().x +
			GivenCollidedObject.GetObjectSprite().getGlobalBounds().width / 2 +
			m_ObjectSprite.getGlobalBounds().width / 2, GetObjectSprite().getPosition().y));
	}
}
//-------------------------------------------//
void MovingNormalFloor::SetLeftMovement()
{
	m_RightMovement = false;
	m_LeftMovement = true;
}
//-------------------------------------------//
void MovingNormalFloor::SetRightMovement()
{
	m_LeftMovement = false;
	m_RightMovement = true;
}
//-------------------------------------------//