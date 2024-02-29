#include "StaticInvisibleFloor.h"
//-------------------------------------------//
static auto registerIt = Factory<StaticObject>::instance().registerType(
	ObjectType::StaticInvisibleFloorSymbol,
	[](sf::Vector2f position) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<StaticInvisibleFloor>(position);
	}
);
//-------------------------------------------//
StaticInvisibleFloor::StaticInvisibleFloor(const sf::Vector2f& Position)
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
void StaticInvisibleFloor::UpdateMyVisibilityStatus(const Monkey& GivenMonkey)
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