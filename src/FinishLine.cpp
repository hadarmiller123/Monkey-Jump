#include "FinishLine.h"
//-------------------------------------------//
static auto registerIt = Factory<StaticObject>::instance().registerType(
	ObjectType::FinishLineSymbol,
	[](sf::Vector2f position) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<FinishLine>(position);
	}
);
//-------------------------------------------//
FinishLine::FinishLine(const sf::Vector2f& Position)
{
	SetNewSpritePosition(Position);

	m_ObjectSprite.setTexture(Resources::Instance().GetFinishLineTexture(*this));
	m_ObjectSprite.setOrigin(sf::Vector2f(m_ObjectSprite.getGlobalBounds().width / 2,
		m_ObjectSprite.getGlobalBounds().height / 2));// setting the origin to the middle
}
//-------------------------------------------//