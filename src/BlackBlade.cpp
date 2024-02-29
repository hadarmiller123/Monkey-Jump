#include "BlackBlade.h"
//-------------------------------------------//
static auto registerIt = Factory<MovingObject>::instance().registerType(
     ObjectType::BlackBladeSymbol,
     [](sf::Vector2f position) -> std::unique_ptr<MovingObject>
     {
         return std::make_unique<BlackBlade>(position);
     }
 );
//-------------------------------------------//
BlackBlade::BlackBlade(const sf::Vector2f& Position)
{
	SetNewSpritePosition(Position);

	m_ObjectSprite.setTexture(Resources::Instance().GetBlackBladeTexture(*this));
	m_ObjectSprite.setOrigin(sf::Vector2f(m_ObjectSprite.getGlobalBounds().width / 2,
		m_ObjectSprite.getGlobalBounds().height / 2));// setting the origin to the middle

	m_ObjectSprite.setScale(m_XScale, m_YScale); // adjast the sprite to 70x70

	// This is the verticis of the square from the middle of the sprite and to his top corner (doesent metter which)
	float SquareSide = m_ObjectSprite.getGlobalBounds().width / 2;

	// A^2 + B^2 = C^2 for the slant from the middle of the blade
	m_DiagonalLine = sqrt(SquareSide * SquareSide + SquareSide * SquareSide);
}
//-------------------------------------------//
void BlackBlade::Move()
{
	m_ObjectSprite.rotate(ROTATE_MOVEMENT);

	if (m_LeftMovement) {
		if (m_ObjectSprite.getPosition().x - m_DiagonalLine < 0.0f) {
			m_LeftMovement = false;
			m_RightMovement = true;
		}
		SetNewSpritePosition(sf::Vector2f(m_ObjectSprite.getPosition().x + m_LeftMovementSpeed, m_ObjectSprite.getPosition().y));
	}
	else if (m_RightMovement) {
		if (m_ObjectSprite.getPosition().x + m_DiagonalLine > float(SCREEN_WIDTH)) {
			m_RightMovement = false;
			m_LeftMovement = true;
		}
		SetNewSpritePosition(sf::Vector2f(m_ObjectSprite.getPosition().x + m_RightMovementSpeed, m_ObjectSprite.getPosition().y));
	}
}
//-------------------------------------------//
void BlackBlade::Collided(const BaseGameObject& GivenCollidedObject)
{
	// If the blade collided with base object from the left
	// we set his movement to right
	if (m_ObjectSprite.getPosition().x <
		GivenCollidedObject.GetObjectSprite().getPosition().x) {

		// Setting the black blade position to the object position decreased by the floor width
		SetLeftMovement();
		// Setting the black blade position to the object position - his width/2 - the *this object width/2
		SetNewSpritePosition(sf::Vector2f(GivenCollidedObject.GetObjectSprite().getPosition().x -
			GivenCollidedObject.GetObjectSprite().getGlobalBounds().width / 2 -
			m_ObjectSprite.getGlobalBounds().width / 2, GetObjectSprite().getPosition().y));
	}
	// The opposite
	else {
		SetRightMovement();

		// Setting the black blade position to the object position + his width/2 + the *this object width/2
		SetNewSpritePosition(sf::Vector2f(GivenCollidedObject.GetObjectSprite().getPosition().x +
			GivenCollidedObject.GetObjectSprite().getGlobalBounds().width / 2 +
			m_ObjectSprite.getGlobalBounds().width / 2, GetObjectSprite().getPosition().y));
	}
}
//-------------------------------------------//
void BlackBlade::SetLeftMovement()
{
	m_RightMovement = false;
	m_LeftMovement = true;
}
//-------------------------------------------//
void BlackBlade::SetRightMovement()
{
	m_LeftMovement = false;
	m_RightMovement = true;
}
//-------------------------------------------//