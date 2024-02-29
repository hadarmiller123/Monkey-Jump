#include "Monkey.h"
//-------------------------------------------//
static auto registerIt = Factory<MovingObject>::instance().registerType(
	ObjectType::MonkeySymbol,
	[](sf::Vector2f position) -> std::unique_ptr<MovingObject>
	{
		return std::make_unique<Monkey>(position);
	}
);
//-------------------------------------------//
Monkey::Monkey(const sf::Vector2f& Position) : 
	MonkeyNewPosition(m_ObjectSprite.getPosition().x, m_ObjectSprite.getPosition().y)
{
	SetNewSpritePosition(Position);

	m_ObjectSprite.setTexture(Resources::Instance().GetMonkeyTexture(*this));
	m_ObjectSprite.setOrigin(sf::Vector2f(m_ObjectSprite.getGlobalBounds().width / 2,
		m_ObjectSprite.getGlobalBounds().height / 2));// setting the origin to the middle
}
//-------------------------------------------//
void Monkey::Move()
{
	InvisibleEffect();

	if (!m_IsMonkeyNewPositionReset) {
		MonkeyNewPosition = sf::Vector2f{ m_ObjectSprite.getPosition().x, m_ObjectSprite.getPosition().y };
		m_IsMonkeyNewPositionReset = true;
	}

	// Down force
	if (!m_Jump) {
		m_Gravity += 0.4f;
		MonkeyNewPosition.y += m_Gravity;
	}

	// Upper force
	if (m_Jump) {
		m_Gravity += 0.4f;
		MonkeyNewPosition.y += m_Gravity;

		if (m_Gravity > 0.0f) {
			m_Jump = false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		MonkeyNewPosition.x -= SIDE_MOVEMENT;

		if (MonkeyNewPosition.x < 0.0f) {
			MonkeyNewPosition.x = float(SCREEN_WIDTH);
		}

		m_ObjectSprite.setScale(-1.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		MonkeyNewPosition.x += SIDE_MOVEMENT;

		if (MonkeyNewPosition.x > float(SCREEN_WIDTH)) {
			MonkeyNewPosition.x = 0.0f;
		}

		m_ObjectSprite.setScale(1.0f, 1.0f);
	}

	SetNewSpritePosition(sf::Vector2f(MonkeyNewPosition.x, MonkeyNewPosition.y));
}
//-------------------------------------------//
void Monkey::SetInvisibilityStatus(const Invisible& InvisibleType)
{
	m_InvisibleClockRestart = true;
}
//-------------------------------------------//
bool Monkey::GetInvisibilityStatus() const
{
	return m_Invisible;
}
//-------------------------------------------//
void Monkey::SetJumpStatus(const float& GivenGravity)
{
	if (GivenGravity >= 0) {
		return;
	}

	m_Gravity = GivenGravity;
	m_Jump = true;
}
//-------------------------------------------//
bool Monkey::GetJumpStatus() const
{
	return m_Jump;
}
//-------------------------------------------//
void Monkey::SetFinishStatus(const FinishLine& GivenFinishLine)
{
	m_Finished = true;
}
//-------------------------------------------//
bool Monkey::GetFinishedStatus() const
{
	return m_Finished;
}
//-------------------------------------------//
void Monkey::InvisibleEffect()
{
	// For the critical part
	static bool MuteX = false;

	if (m_InvisibleClockRestart) {
		m_InvisibleClockRestart = false;
		MuteX = true;
		m_ObjectSprite.setColor(sf::Color(150, 150, 150, 150));
		m_Invisible = true;
		m_InvisibleClock.restart();
	}

	if (m_InvisibleClock.getElapsedTime().asSeconds() > 5 && MuteX) {
		m_ObjectSprite.setColor(sf::Color(255, 255, 255, 255));
		m_Invisible = false;
		MuteX = false;
	}
}
//-------------------------------------------//