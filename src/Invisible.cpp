#include "Invisible.h"
//-------------------------------------------//
static auto registerIt = Factory<StaticObject>::instance().registerType(
	ObjectType::InvisibleSymbol,
	[](sf::Vector2f position) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Invisible>(position);
	}
);
//-------------------------------------------//
Invisible::Invisible(const sf::Vector2f& Position)
{
	SetNewSpritePosition(Position);

	m_ObjectSprite.setTexture(Resources::Instance().GetInvisibleTexture(*this));
	m_ObjectSprite.setOrigin(sf::Vector2f(m_ObjectSprite.getGlobalBounds().width / 2,
		m_ObjectSprite.getGlobalBounds().height / 2));// setting the origin to the middle
}
//-------------------------------------------//
void Invisible::Draw(sf::RenderWindow& GivenScreen)
{
	BlurGlowEffect();

	GivenScreen.draw(m_ObjectSprite);
}
//-------------------------------------------//
void Invisible::BlurGlowEffect()
{
	static float BluryAmount = 255.0f;
	static bool BluryStatus = true;

	if (BluryStatus && BluryAmount > 180.0f) {
		// Set object color blurier
		BluryAmount -= 1.0f;
		m_ObjectSprite.setColor(sf::Color(sf::Uint8(BluryAmount), sf::Uint8(BluryAmount), sf::Uint8(BluryAmount), sf::Uint8(BluryAmount)));
		
	}
	else {
		if (BluryStatus) {
			BluryStatus = false;
		}
		// Glowing effect (the opposite from blur)
		BluryAmount += 1.0f;
		m_ObjectSprite.setColor(sf::Color(sf::Uint8(BluryAmount), sf::Uint8(BluryAmount), sf::Uint8(BluryAmount), sf::Uint8(BluryAmount)));

		if (BluryAmount >= 255.0f) {
			BluryStatus = true;
		}
	}
}
//-------------------------------------------//