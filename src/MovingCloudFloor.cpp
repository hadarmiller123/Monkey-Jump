#include "MovingCloudFloor.h"
//-------------------------------------------//
static auto registerIt = Factory<MovingObject>::instance().registerType(
	ObjectType::MovingCloudFloorSymbol,
	[](sf::Vector2f position) -> std::unique_ptr<MovingObject>
	{
		return std::make_unique<MovingCloudFloor>(position);
	}
);
//-------------------------------------------//
MovingCloudFloor::MovingCloudFloor(const sf::Vector2f& Position)
{
	SetNewSpritePosition(Position);

	m_ObjectSprite.setTexture(Resources::Instance().GetCloudFloorTexture(*this));
	m_ObjectSprite.setOrigin(sf::Vector2f(m_ObjectSprite.getGlobalBounds().width / 2,
		m_ObjectSprite.getGlobalBounds().height));// setting the origin to the bottom middle

	// Scaling the sprite size to be 100 x 50
	m_ObjectSprite.setScale(100.0f/193.0f, 50.0f/80.0f);

	// Initializes gravity to normal floor gravity
	m_Gravity = -15.0f;
}
//-------------------------------------------//
void MovingCloudFloor::Move()
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
void MovingCloudFloor::Collided(const BaseGameObject& GivenCollidedObject)
{
	// If the floor collided with base object from the left
	// we set his movement to right
	if (m_ObjectSprite.getPosition().x <
		GivenCollidedObject.GetObjectSprite().getPosition().x) {

		// Setting the floor position to the object position decreased by the floor width
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
void MovingCloudFloor::SetLeftMovement()
{
	m_RightMovement = false;
	m_LeftMovement = true;
}
//-------------------------------------------//
void MovingCloudFloor::SetRightMovement()
{
	m_LeftMovement = false;
	m_RightMovement = true;
}
//-------------------------------------------//