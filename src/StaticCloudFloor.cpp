#include "StaticCloudFloor.h"
//-------------------------------------------//
static auto registerIt = Factory<StaticObject>::instance().registerType(
	ObjectType::StaticCloudFloorSymbol,
	[](sf::Vector2f position) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<StaticCloudFloor>(position);
	}
);
//-------------------------------------------//
StaticCloudFloor::StaticCloudFloor(const sf::Vector2f& Position)
{
	SetNewSpritePosition(Position);

	m_ObjectSprite.setTexture(Resources::Instance().GetCloudFloorTexture(*this));
	m_ObjectSprite.setOrigin(sf::Vector2f(m_ObjectSprite.getGlobalBounds().width / 2,
		m_ObjectSprite.getGlobalBounds().height));// setting the origin to the bottom middle

	// Scaling the object to be 100x50
	m_ObjectSprite.setScale(100.0f/193.0f, 50.0f/80.0f);

	// Initializes gravity to normal floor gravity
	m_Gravity = -15.0f;
}
//-------------------------------------------//