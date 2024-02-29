#pragma once
//-----------------------------------------------//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h> // For abs()
#include "Resources.h"
#include "Monkey.h"
//-----------------------------------------------//
class WindowGraphic
{
public:
	WindowGraphic();

	// Get window function in order to send them the window for drawing themselfs
	sf::RenderWindow& GetMyWindow();
	bool DisplayMyWindow();
	void DisplayGameIntro();

	// Updating game view as the monkey position
	void SetGameView(const Monkey& GivenMonkey);
	sf::View GetGameView() const;

	void HomePageReset();
private:
	void LoadGameSprites();
	void LoadGameSound();
	void LoadMenuSprites();
	void SetReactButtons();
	void DisplayLogo();
	void DisplayLoadingIntro();
	void RunMenuPage(const sf::Vector2i& MousePos);
	void RunStartPage(const sf::Vector2i& MousePos);
	void RunHelpPage(const sf::Vector2i& MousePos);
	void RunSoundPage();

private:
	sf::RenderWindow m_GameScreen;
	sf::Event m_ScreenEvents;

	// Intro objects
	sf::Sprite m_IntroSprites[INTRO_FRAMES];

	// Logo objects;
	sf::Sprite m_LogoSprites[LOGO_FRAMES];
	sf::Sound m_LogoSound;

	// Menu objects
	sf::Sprite m_MenuSprites[MENU_SPRITES];// 0 = Menu, 1 = Play, 2 = Help, 3 = Sound, 4 = Exit //
	sf::IntRect m_ButtonsArea[MENU_SPRITES - 1]; // For Start, Help, Credits, Exit//

	//General game music
	sf::Music m_GameMusic;

	// Game backround
	sf::Sprite m_GameBackround;

	sf::View m_GameView;

	// Help page object
	sf::Sprite m_HelpPageSprite;

	// Home button object
	sf::Sprite m_HomeButtonSprite;
	sf::IntRect m_HomeButtonArea;

	// Will be represent the status of which page is running
	bool m_ButtonPressed[MENU_SPRITES - 1] = { true, false, false, false};
};
//-------------------------------------------//