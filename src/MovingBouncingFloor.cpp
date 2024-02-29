#include "MovingBouncingFloor.h"
//-------------------------------------------//
static auto registerIt = Factory<MovingObject>::instance().registerType(
	ObjectType::MovingBouncingFloorSymbol,
	[](sf::Vector2f position) -> std::unique_ptr<MovingObject>
	{
		return std::make_unique<MovingBouncingFloor>(position);
	}
);
//-------------------------------------------//
MovingBouncingFloor::MovingBouncingFloor(const sf::Vector2f& Position)
{
	SetNewSpritePosition(Position);

	m_ObjectSprite.setTexture(Resources::Instance().GetBouncingFloorTexture(*this));
	m_ObjectSprite.setOrigin(sf::Vector2f(m_ObjectSprite.getGlobalBounds().width / 2,
		m_ObjectSprite.getGlobalBounds().height));// setting the origin to the bottom middle

	// Scaling the sprite to be 100 x 50
	m_ObjectSprite.setScale(1.0f, 0.5f);

	m_Gravity = -28.0f;
}
//-------------------------------------------//
void MovingBouncingFloor::Move()
{
	// Setting the floor movement to the longest side / default = left charging movement if
	// the blade is in the right half side of the screen of the blade is in the middle of the screen
	if (m_ObjectSprite.getPosition().x < SCREEN_WIDTH / 2.0f && !m_ChangeDefaultMovementSides) {
		m_LeftMovement = false;
		m_RightMovement = true;
	}

	if (!m_ChangeDefaultMovementSides) {
		m_ChangeDefaultMovementSides = true;
	}

	// Setting the floor movement to the longest side / default = left charging movement if
	// the blade is in the right half side of the screen of the blade is in the middle of the screen
	if (m_ObjectSprite.getPosition().x < SCREEN_WIDTH / 2.0f && !m_ChangeDefaultMovementSides) {
		m_LeftMovement = false;
		m_RightMovement = true;
	}

	if (!m_ChangeDefaultMovementSides) {
		m_ChangeDefaultMovementSides = true;
	}

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
void MovingBouncingFloor::Collided(const BaseGameObject& GivenCollidedObject)
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
void MovingBouncingFloor::Draw(sf::RenderWindow& GivenScreen)
{
	if (m_IsBouncing) {
		m_ObjectSprite.setScale(1.0f, 1.0f);
	}

	GivenScreen.draw(m_ObjectSprite);
}
//-------------------------------------------//
void MovingBouncingFloor::SetBouncingStatus()
{
	m_IsBouncing = true;
}
//-------------------------------------------//
void MovingBouncingFloor::SetLeftMovement()
{
	m_RightMovement = false;
	m_LeftMovement = true;
}
//-------------------------------------------//
void MovingBouncingFloor::SetRightMovement()
{
	m_LeftMovement = false;
	m_RightMovement = true;
}
//-------------------------------------------//