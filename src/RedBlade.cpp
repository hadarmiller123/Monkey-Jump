#include "RedBlade.h"
//-------------------------------------------//
static auto registerIt = Factory<MovingObject>::instance().registerType(
	ObjectType::RedBladeSymbol,
	[](sf::Vector2f position) -> std::unique_ptr<MovingObject>
	{
		return std::make_unique<RedBlade>(position);
	}
);
//-------------------------------------------//
RedBlade::RedBlade(const sf::Vector2f& Position)
{
	SetNewSpritePosition(Position);

	m_ObjectSprite.setTexture(Resources::Instance().GetRedBladeTexture(*this));
	m_ObjectSprite.setOrigin(sf::Vector2f(GetObjectSprite().getGlobalBounds().width / 2,
		m_ObjectSprite.getGlobalBounds().height / 2));// setting the origin to the middle

	m_ObjectSprite.setScale(m_XScale, m_YScale); // adjast the sprite to 70x70

	// This is the verticis of the square from the middle of the sprite and to his top corner (doesent metter which)
	float SquareSide = m_ObjectSprite.getGlobalBounds().width / 2;

	// A^2 + B^2 = C^2 for the slant from the middle of the blade
	m_DiagonalLine = sqrt(SquareSide * SquareSide + SquareSide * SquareSide);
}
//-------------------------------------------//
void RedBlade::Move()
{
	// Setting the blade charging movement to charge the longest side / default = left charging movement if
	// the blade is in the right half side of the screen of the blade is in the middle of the screen
	if (m_ObjectSprite.getPosition().x < SCREEN_WIDTH / 2.0f && !m_ChangeDefaultChargingSides) {
		m_LeftCharging = false;
		m_RightCharging = true;
	}

	if (!m_ChangeDefaultChargingSides) {
		m_ChangeDefaultChargingSides = true;
	}

	m_ObjectSprite.rotate(ROTATE_MOVEMENT);

	if (!m_Charge) {
		ChargingEffect();
		return;
	}
	else if (m_Charge) {
		if (m_LeftCharging) {
			if (m_ObjectSprite.getPosition().x - m_DiagonalLine * 2 < 0.0f) {
				m_LeftCharging = false;
				m_RightCharging = true;
				m_Charge = false;
				SetNewSpritePosition(sf::Vector2f(m_DiagonalLine, GetObjectSprite().getPosition().y));

				return;
			}
			SetNewSpritePosition(sf::Vector2f(GetObjectSprite().getPosition().x + m_LeftChargingSpeed, GetObjectSprite().getPosition().y));
		}
		else if (m_RightCharging) {
			if (m_ObjectSprite.getPosition().x + m_DiagonalLine * 2 > float(SCREEN_WIDTH)) {
				m_RightCharging = false;
				m_LeftCharging = true;
				m_Charge = false;
				SetNewSpritePosition(sf::Vector2f(float(SCREEN_WIDTH) - m_DiagonalLine, GetObjectSprite().getPosition().y));

				return;
			}
			SetNewSpritePosition(sf::Vector2f(GetObjectSprite().getPosition().x + m_RightChargingSpeed, GetObjectSprite().getPosition().y));
		}

		return;
	}
}
//-------------------------------------------//
void RedBlade::Collided(const BaseGameObject& GivenCollidedObject)
{
	// If the blade collided with base object from the left
	// we set his movement to right
	if (m_ObjectSprite.getPosition().x <
		GivenCollidedObject.GetObjectSprite().getPosition().x) {

		// Setting the blade position to the object position decreased by the floor width
		SetLeftCharging();
		SetNewSpritePosition(sf::Vector2f(GivenCollidedObject.GetObjectSprite().getPosition().x -
			GivenCollidedObject.GetObjectSprite().getGlobalBounds().width / 2 - m_DiagonalLine, GetObjectSprite().getPosition().y));
	}
	// The opposite
	else {
		SetRightCharging();

		// Setting the blade position to the object position increasing by the object width
		SetNewSpritePosition(sf::Vector2f(GivenCollidedObject.GetObjectSprite().getPosition().x +
			GivenCollidedObject.GetObjectSprite().getGlobalBounds().width / 2 + m_DiagonalLine, GetObjectSprite().getPosition().y));
	}
}
//-------------------------------------------//
void RedBlade::SetLeftCharging()
{
	m_RightCharging = false;
	m_LeftCharging = true;

	m_Charge = false;
}
//-------------------------------------------//
void RedBlade::SetRightCharging()
{
	m_LeftCharging = false;
	m_RightCharging = true;

	m_Charge = false;
}
//-------------------------------------------//
void RedBlade::ChargingEffect()
{
	if (m_x > 0.1 && m_y > 0.1) {
		m_x -= 0.004f;
		m_y -= 0.004f;
	}
	else {
		m_x = m_XScale;
		m_y = m_YScale;
		m_Charge = true;
	}

	m_ObjectSprite.setScale(m_x, m_y);
}
//-------------------------------------------//