#include "MovingInvisibleFloor.h"
//-------------------------------------------//
static auto registerIt = Factory<MovingObject>::instance().registerType(
	ObjectType::MovingInvisibleFloorSymbol,
	[](sf::Vector2f position) -> std::unique_ptr<MovingObject>
	{
		return std::make_unique<MovingInvisibleFloor>(position);
	}
);
//-------------------------------------------//
MovingInvisibleFloor::MovingInvisibleFloor(const sf::Vector2f& Position)
{
	SetNewSpritePosition(Position);

	m_ObjectSprite.setTexture(Resources::Instance().GetInvisibleFloorTexture(*this));
	m_ObjectSprite.setOrigin(sf::Vector2f(m_ObjectSprite.getGlobalBounds().width / 2,
		m_ObjectSprite.getGlobalBounds().height));// setting the origin to the bottom middle

	// Default color is half transperent (unvisible)
	m_ObjectSprite.setColor(sf::Color(255, 255, 255, 100));

	m_Gravity = -14.0f;
}
//-------------------------------------------//
void MovingInvisibleFloor::Move()
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
void MovingInvisibleFloor::Collided(const BaseGameObject& GivenCollidedObject)
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
void MovingInvisibleFloor::UpdateMyVisibilityStatus(const Monkey& GivenMonkey)
{
	if (GivenMonkey.GetInvisibilityStatus()) {
		m_ObjectSprite.setColor(sf::Color(255, 255, 255, 255));

		// If the monkey sprite above the floor sprite we change the visibility of the floor
		// such as the monkey could land on it
		if (GivenMonkey.GetObjectSprite().getGlobalBounds().top + GivenMonkey.GetObjectSprite().getGlobalBounds().height <=
			GetObjectSprite().getGlobalBounds().top) {
			if (m_Visible != true) {
				m_Visible = true;
			}
		}
		// If the monkey sprite not fully above the floor he just can go through the floor from down
		else {
			if (GetVisibleStatus() != false) {
				m_Visible = false;
			}
		}
	}
	else {
		m_Visible = false;
		m_ObjectSprite.setColor(sf::Color(255, 255, 255, 100));
	}
}
//-------------------------------------------//
void MovingInvisibleFloor::SetLeftMovement()
{
	m_RightMovement = false;
	m_LeftMovement = true;
}
//-------------------------------------------//
void MovingInvisibleFloor::SetRightMovement()
{
	m_LeftMovement = false;
	m_RightMovement = true;
}
//-------------------------------------------//