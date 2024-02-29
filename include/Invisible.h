#pragma once
//-------------------------------------------//
#include "StaticObject.h"
#include "Resources.h"
#include "Factory.h"
//-------------------------------------------//
class Invisible : public StaticObject
{
public:
	Invisible(const sf::Vector2f& Position);
	// Override draw function in order to make the Blur Glow Effect
	virtual void Draw(sf::RenderWindow& ScreenGiven) override;
private:
	void BlurGlowEffect();
};
//-------------------------------------------//