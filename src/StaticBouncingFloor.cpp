#include "StaticBouncingFloor.h"
//-------------------------------------------//
static auto registerIt = Factory<StaticObject>::instance().registerType(
	ObjectType::StaticBouncingFloorSymbol,
	[](sf::Vector2f position) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<StaticBouncingFloor>(position);
	}
);
//-------------------------------------------//
StaticBouncingFloor::StaticBouncingFloor(const sf::Vector2f& Position)
{
	SetNewSpritePosition(Position);

	m_ObjectSprite.setTexture(Resources::Instance().GetBouncingFloorTexture(*this));
	m_ObjectSprite.setOrigin(sf::Vector2f(m_ObjectSprite.getGlobalBounds().width / 2,
		m_ObjectSprite.getGlobalBounds().height));// setting the origin to the bottom middle

	m_ObjectSprite.setScale(1.0f, 0.5f);

	m_Gravity = -28.0f;
}
//-------------------------------------------//
void StaticBouncingFloor::Draw(sf::RenderWindow& GivenScreen)
{
	if (m_IsBouncing) {
		m_ObjectSprite.setScale(1.0f, 1.0f);
	}

	GivenScreen.draw(m_ObjectSprite);
}
//-------------------------------------------//
void StaticBouncingFloor::SetBouncingStatus()
{
	m_IsBouncing = true;
}
//-------------------------------------------//