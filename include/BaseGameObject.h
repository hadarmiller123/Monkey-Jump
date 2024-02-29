#pragma once
//-------------------------------------------//
#include <SFML/Graphics.hpp>
//-------------------------------------------//
class BaseGameObject
{
public:
	BaseGameObject();
	virtual ~BaseGameObject() = default;
	virtual void Draw(sf::RenderWindow& GivenScreen);
	sf::Sprite GetObjectSprite() const;

	// For setting new position to the sprite object
	void SetNewSpritePosition(const sf::Vector2f& GivenNewPosition);

	bool GetDisposedStatus() const;

	// Virtual becuase each object could make animation and sound as well when they need to be disposed
	virtual void SetDisposedStatus();
protected:
	sf::Vector2f m_Position;
	sf::Sprite m_ObjectSprite;
	bool m_IsDisposed = false;
private:
};
//-------------------------------------------//