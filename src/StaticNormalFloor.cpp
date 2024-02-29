#include "StaticNormalFloor.h"
//-------------------------------------------//
static auto registerIt = Factory<StaticObject>::instance().registerType(
	ObjectType::StaticNormalFloorSymbol,
	[](sf::Vector2f position) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<StaticNormalFloor>(position);
	}
);
//-------------------------------------------//
StaticNormalFloor::StaticNormalFloor(const sf::Vector2f& Position)
{
	SetNewSpritePosition(Position);

	m_ObjectSprite.setTexture(Resources::Instance().GetNormalFloorTexture(*this));
	m_ObjectSprite.setOrigin(sf::Vector2f(m_ObjectSprite.getGlobalBounds().width / 2,
		m_ObjectSprite.getGlobalBounds().height));// setting the origin to the bottom middle

	// Initializes gravity to normal floor gravity
	m_Gravity = -14.0f;
}
//-------------------------------------------//