#include "Resources.h"
//-----------------------------------------------//
Resources::Resources()
{
	// Loading objects textures //
	LoadGameTextures();

	// Loading game sound and intro sound //
	LoadGameSoundBuffers();
}
//-----------------------------------------------//
void Resources::LoadGameTextures()
{
	// Loading for each cell the currect intro frame of the intro
	for (int index = 0; index < INTRO_FRAMES; ++index)
	{
		switch (index)
		{
		case 0:
			if (!m_IntroTextures[index].loadFromFile("Intro1.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 1:
			if (!m_IntroTextures[index].loadFromFile("Intro2.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 2:
			if (!m_IntroTextures[index].loadFromFile("Intro3.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 3:
			if (!m_IntroTextures[index].loadFromFile("Intro4.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 4:
			if (!m_IntroTextures[index].loadFromFile("Intro5.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 5:
			if (!m_IntroTextures[index].loadFromFile("Intro6.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 6:
			if (!m_IntroTextures[index].loadFromFile("Intro7.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 7:
			if (!m_IntroTextures[index].loadFromFile("Intro8.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 8:
			if (!m_IntroTextures[index].loadFromFile("Intro9.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		default:
			break;
		}
	}

	// Loading for each cell the currect intro frame of the logo
	for (int index = 0; index < LOGO_FRAMES; ++index)
	{
		switch (index)
		{
		case 0:
			if (!m_LogoTextures[index].loadFromFile("MonkeyLogo1.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 1:
			if (!m_LogoTextures[index].loadFromFile("MonkeyLogo2.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 2:
			if (!m_LogoTextures[index].loadFromFile("MonkeyLogo3.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		default:
			break;
		}
	}

	// Loading for each cell the currect menu backround and menu buttons //
	for (int index = 0; index < MENU_SPRITES; ++index)
	{
		switch (index)
		{
		case 0:
			if (!m_MenuTexturesHolder[index].loadFromFile("Menu.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 1:
			if (!m_MenuTexturesHolder[index].loadFromFile("PlayButton.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 2:
			if (!m_MenuTexturesHolder[index].loadFromFile("HelpButton.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 3:
			if (!m_MenuTexturesHolder[index].loadFromFile("SoundButton.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		case 4:
			if (!m_MenuTexturesHolder[index].loadFromFile("ExitButton.png")) {
				exit(EXIT_FAILURE);
			}
			break;
		default:
			break;
		}
	}

	if (!m_GameBackroundTextureHolder.loadFromFile("GameBackround.png")) {
		exit(EXIT_FAILURE);
	}

	if (!m_HomeButtonTextureHolder.loadFromFile("HomeButton.png")) {
		exit(EXIT_FAILURE);
	}

	if (!m_HelpPageTextureHolder.loadFromFile("Help.png")) {
		exit(EXIT_FAILURE);
	}

	// to make function who load game objects textures //

	if (!m_MonkeyTextureHolder.loadFromFile("Monkey.png")) {
		exit(EXIT_FAILURE);
	}

	if (!m_BlackBladeTextureHolder.loadFromFile("BlackBlade.png")) {
		exit(EXIT_FAILURE);
	}

	if (!m_RedBladeTextureHolder.loadFromFile("RedBlade.png")) {
		exit(EXIT_FAILURE);
	}

	if (!m_InvisibleTextureHolder.loadFromFile("Invisible.png")) {
		exit(EXIT_FAILURE);
	}

	if (!m_NormalFloorTextureHolder.loadFromFile("NormalFloor.png")) {
		exit(EXIT_FAILURE);
	}

	if (!m_InvisibleFloorTextureHolder.loadFromFile("InvisibleFloor.png")) {
		exit(EXIT_FAILURE);
	}

	if (!m_BouncingFloorTextureHolder.loadFromFile("BouncingFloor.png")) {
		exit(EXIT_FAILURE);
	}

	if (!m_CloudFloorTextureHolder.loadFromFile("CloudFloor.png")) {
		exit(EXIT_FAILURE);
	}

	if (!m_FinishLineTextureHolder.loadFromFile("FinishLine.png")) {
		exit(EXIT_FAILURE);
	}
}
//-----------------------------------------------//
void Resources::LoadGameSoundBuffers()
{
	if (!m_LogoSoundBuffer.loadFromFile("LogoSound.wav")) {
		exit(EXIT_FAILURE);
	}
}
//-----------------------------------------------//
const sf::Texture* Resources::GetIntroTexturesArray(const WindowGraphic& WindowType) const
{
	return m_IntroTextures;
}
//-----------------------------------------------//
const sf::Texture* Resources::GetLogoTexturesArray(const WindowGraphic& WindowType) const
{
	return m_LogoTextures;
}
//-----------------------------------------------//
const sf::SoundBuffer& Resources::GetLogoSoundBuffer(const WindowGraphic& WindowType) const
{
	return m_LogoSoundBuffer;
}
//-----------------------------------------------//
const sf::Texture* Resources::GetMenuTexturesArray(const WindowGraphic& WindowType) const
{

	return m_MenuTexturesHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetGameBackroundTexture(const WindowGraphic& WindowType) const
{
	return m_GameBackroundTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetHomeButtonTexture(const WindowGraphic& WindowType) const
{
	return m_HomeButtonTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetHelpPageTexture(const WindowGraphic& WindowType) const
{
	return m_HelpPageTextureHolder;
}
const sf::Texture& Resources::GetMonkeyTexture(const Monkey& MonkeyType) const
{
	return m_MonkeyTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetBlackBladeTexture(const BlackBlade& BladeType) const
{
	return m_BlackBladeTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetRedBladeTexture(const RedBlade& RedBladeType) const
{
	return m_RedBladeTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetInvisibleTexture(const Invisible& InvisibleType) const
{
	return m_InvisibleTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetNormalFloorTexture(const StaticNormalFloor& StaticNormalFloorType) const
{
	return m_NormalFloorTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetNormalFloorTexture(const MovingNormalFloor& MovingNormalFloorType) const
{
	return m_NormalFloorTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetInvisibleFloorTexture(const StaticInvisibleFloor& StaticInvisibleFloorType) const
{
	return m_InvisibleFloorTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetInvisibleFloorTexture(const MovingInvisibleFloor& MovingInvisibleFloorType) const
{
	return m_InvisibleFloorTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetBouncingFloorTexture(const StaticBouncingFloor& StaticBouncingFloorType) const
{
	return m_BouncingFloorTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetBouncingFloorTexture(const MovingBouncingFloor& MovingBouncingFloorType) const
{
	return m_BouncingFloorTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetCloudFloorTexture(const StaticCloudFloor& StaticCloudFloorType) const
{
	return m_CloudFloorTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetCloudFloorTexture(const MovingCloudFloor& MovingCloudFloorType) const
{
	return m_CloudFloorTextureHolder;
}
//-----------------------------------------------//
const sf::Texture& Resources::GetFinishLineTexture(const FinishLine& FinishLineType) const
{
	return m_FinishLineTextureHolder;
}
//-----------------------------------------------//