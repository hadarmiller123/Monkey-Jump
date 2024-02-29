#include "BaseGameObject.h"
//-------------------------------------------//
BaseGameObject::BaseGameObject() : m_Position(0.0f, 0.0f) {}
//-------------------------------------------//
void BaseGameObject::SetNewSpritePosition(const sf::Vector2f& GivenNewPosition)
{
	m_Position = GivenNewPosition;

	m_ObjectSprite.setPosition(m_Position);
}
//-------------------------------------------//
void BaseGameObject::Draw(sf::RenderWindow& GivenScreen)
{
	GivenScreen.draw(m_ObjectSprite);
}
//-------------------------------------------//
sf::Sprite BaseGameObject::GetObjectSprite() const
{
	return m_ObjectSprite;
}
//-------------------------------------------//
bool BaseGameObject::GetDisposedStatus() const
{
	return m_IsDisposed;
}
//-------------------------------------------//
void BaseGameObject::SetDisposedStatus()
{
	m_IsDisposed = true;
}
//-------------------------------------------//