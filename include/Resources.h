#pragma once
//-----------------------------------------------//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//-----------------------------------------------//
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;

const int INTRO_FRAMES = 9;
const int LOGO_FRAMES = 3;
const int MENU_SPRITES = 5;// 0 = Menu, 1 = Play, 2 = Help, 3 = Sound, 4 = Exit
//-----------------------------------------------//
class WindowGraphic;
class Monkey;
class BlackBlade;
class RedBlade;
class Invisible;
class StaticNormalFloor;
class StaticInvisibleFloor;
class StaticBouncingFloor;
class StaticCloudFloor;
class MovingNormalFloor;
class MovingInvisibleFloor;
class MovingBouncingFloor;
class MovingCloudFloor;
class FinishLine;
//-----------------------------------------------//
class Resources
{
public:
	Resources();

	// Making a static C-tor and deleting all equal and copy constructor option
	static Resources& Instance() {
		static auto resources = Resources();
		return resources;
	}
	Resources(const Resources&) = delete;
	void operator=(const Resources&) = delete;

	const sf::Texture* GetIntroTexturesArray(const WindowGraphic& WindowType) const;
	const sf::Texture* GetLogoTexturesArray(const WindowGraphic& WindowType) const;
	const sf::SoundBuffer& GetLogoSoundBuffer(const WindowGraphic& WindowType) const;
	const sf::Texture* GetMenuTexturesArray(const WindowGraphic& WindowType) const;
	const sf::Texture& GetGameBackroundTexture(const WindowGraphic& WindowType) const;
	const sf::Texture& GetHomeButtonTexture(const WindowGraphic& WindowType) const;
	const sf::Texture& GetHelpPageTexture(const WindowGraphic& WindowType) const;
	const sf::Texture& GetMonkeyTexture(const Monkey& MonkeyType) const;
	const sf::Texture& GetBlackBladeTexture(const BlackBlade& BlackBladeType) const;
	const sf::Texture& GetRedBladeTexture(const RedBlade& RedBladeType) const;
	const sf::Texture& GetInvisibleTexture(const Invisible& InvisibleType) const;

	// Each of the texture return functions implement with argument list type of static floor and moving floor
	// but returns the same texture
	const sf::Texture& GetNormalFloorTexture(const StaticNormalFloor& StaticNormalFloorType) const;
	const sf::Texture& GetNormalFloorTexture(const MovingNormalFloor& MovingNormalFloorType) const;

	const sf::Texture& GetInvisibleFloorTexture(const StaticInvisibleFloor& StaticInvisibleFloorType) const;
	const sf::Texture& GetInvisibleFloorTexture(const MovingInvisibleFloor& MovingInvisibleFloorType) const;
	
	const sf::Texture& GetBouncingFloorTexture(const StaticBouncingFloor& StaticBouncingFloorType) const;
	const sf::Texture& GetBouncingFloorTexture(const MovingBouncingFloor& MovingBouncingFloorType) const;

	const sf::Texture& GetCloudFloorTexture(const StaticCloudFloor& StaticCloudFloorType) const;
	const sf::Texture& GetCloudFloorTexture(const MovingCloudFloor& MovingCloudFloorType) const;

	const sf::Texture& GetFinishLineTexture(const FinishLine& FinishLineType) const;
private:
	void LoadGameTextures();
	void LoadGameSoundBuffers();

private:
	// intro frames (pictures) will be sorted by start to the end
	sf::Texture m_IntroTextures[INTRO_FRAMES];

	// Logo objects
	sf::Texture m_LogoTextures[LOGO_FRAMES];
	sf::SoundBuffer m_LogoSoundBuffer;

	// Menu Objects
	sf::Texture m_MenuTexturesHolder[MENU_SPRITES];

	sf::Texture m_GameBackroundTextureHolder;
	sf::Texture m_HomeButtonTextureHolder;
	sf::Texture m_HelpPageTextureHolder;

	sf::Texture m_MonkeyTextureHolder;
	sf::Texture m_BlackBladeTextureHolder;
	sf::Texture m_RedBladeTextureHolder;
	sf::Texture m_InvisibleTextureHolder;
	sf::Texture m_NormalFloorTextureHolder;
	sf::Texture m_InvisibleFloorTextureHolder;
	sf::Texture m_BouncingFloorTextureHolder;
	sf::Texture m_CloudFloorTextureHolder;
	sf::Texture m_FinishLineTextureHolder;
};
//-------------------------------------------//