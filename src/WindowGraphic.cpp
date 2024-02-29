#include "WindowGraphic.h"
//-----------------------------------------------//
WindowGraphic::WindowGraphic() : 
	m_GameScreen(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Monkey Jump", sf::Style::Close | sf::Style::Titlebar),
	m_ScreenEvents(), m_GameView(sf::Vector2f(float(SCREEN_WIDTH) / 2, float(SCREEN_HEIGHT) / 2), 
		sf::Vector2f(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)))
{
	m_GameScreen.setFramerateLimit(60);

	// Loading logo, intro and menu sprites
	LoadGameSprites();

	// Loading logo, into and menu sound
	LoadGameSound();
}
//-----------------------------------------------//
void WindowGraphic::LoadGameSprites()
{
	for (int index = 0; index < INTRO_FRAMES; ++index)
	{
		m_IntroSprites[index].setTexture(Resources::Instance().GetIntroTexturesArray(*this)[index]);
	}

	for (int index = 0; index < LOGO_FRAMES; ++index)
	{
		m_LogoSprites[index].setTexture(Resources::Instance().GetLogoTexturesArray(*this)[index]);
	}

	m_GameBackround.setTexture(Resources::Instance().GetGameBackroundTexture(*this));
	m_GameBackround.setOrigin(m_GameView.getCenter()); // Setting the backround of the game as the center of the view for the following effect

	m_HelpPageSprite.setTexture(Resources::Instance().GetHelpPageTexture(*this));

	m_HomeButtonSprite.setTexture(Resources::Instance().GetHomeButtonTexture(*this));
	m_HomeButtonSprite.setOrigin(100.0f, 100.0f);
	m_HomeButtonSprite.setPosition(float(SCREEN_WIDTH / 2), 750.0f);

	LoadMenuSprites();
}
//-----------------------------------------------//
void WindowGraphic::LoadGameSound()
{
	m_LogoSound.setBuffer(Resources::Instance().GetLogoSoundBuffer(*this));

	// Loading the theme song //
	if (!m_GameMusic.openFromFile("GameMusic.wav")) {
		exit(EXIT_FAILURE);
	}
}
//-----------------------------------------------//
void WindowGraphic::LoadMenuSprites()
{
	for (int index = 0; index < MENU_SPRITES; ++index)
	{
		m_MenuSprites[index].setTexture(Resources::Instance().GetMenuTexturesArray(*this)[index]);

		if (index != 0) {
			m_MenuSprites[index].setOrigin(100.0f, 100.0f);// Setting each button except the menu page to the middle
		}

		switch (index)
		{
		case 1:
			// Start at top left
			m_MenuSprites[index].setPosition(250.0f, 250.0f);
			break;
		case 2:
			// Help at top right
			m_MenuSprites[index].setPosition(650.0f, 250.0f);
			break;
		case 3:
			// Credits at bottom left
			m_MenuSprites[index].setPosition(250.0f, 650.0f);
			break;
		case 4:
			// Exit at bottom right
			m_MenuSprites[index].setPosition(650.0f, 650.0f);
			break;
		default:
			break;
		}
	}

	SetReactButtons();
}
//-----------------------------------------------//
void WindowGraphic::SetReactButtons()
{
	// For menu buttons
	for (int index = 0; index < MENU_SPRITES - 1; ++index) {
		m_ButtonsArea[index] = sf::IntRect(m_MenuSprites[index + 1].getGlobalBounds());
	}

	// For home button
	m_HomeButtonArea = sf::IntRect(m_HomeButtonSprite.getGlobalBounds());
}
//-----------------------------------------------//
sf::RenderWindow& WindowGraphic::GetMyWindow()
{
	return m_GameScreen;
}
//-----------------------------------------------//
bool WindowGraphic::DisplayMyWindow()
{
	while (m_GameScreen.pollEvent(m_ScreenEvents)) {
		switch (m_ScreenEvents.type)
		{
		case sf::Event::Closed:
			m_GameScreen.close();
			break;
		}
	}

	m_GameScreen.clear();

	// Define Mouse position for checking //
	// if mouse is on one of the buttons //
	sf::Vector2i MousePos = sf::Mouse::getPosition(m_GameScreen);

	// Loop for running and handling each page after a button was pressed //
	for (int index = 0; index < MENU_SPRITES - 2; ++index) {
		if (m_ButtonPressed[index]) {
			switch (index)
			{
			case 0:
				RunMenuPage(MousePos);
				if (m_ButtonPressed[1]) { // if Start button was pressed
					continue; // we continue stright away to run start page
				}
				else {
					break;
				}
			case 1:
				RunStartPage(MousePos);
				break;
			case 2:
				//std::cout << "in Help" << std::endl;
				RunHelpPage(MousePos);
				break;
			}
		}
	}

	// Seting the song in a loop that will play as long as menu appears //
	if (m_GameMusic.getStatus() != sf::Music::Playing && !m_ButtonPressed[3]) {
		m_GameMusic.setLoop(true);
		m_GameMusic.setVolume(40.0f);
		m_GameMusic.play();
	}
	else if (m_ButtonPressed[3]) {
		m_GameMusic.pause();
	}

	return(m_ButtonPressed[1]);// Returning false if Start button wasn't pressed yet
}
//-----------------------------------------------//
void WindowGraphic::DisplayGameIntro()
{
	DisplayLogo();

	DisplayLoadingIntro();
}
//-----------------------------------------------//
void WindowGraphic::DisplayLogo()
{
	sf::Clock LogoClock;

	bool IsLogoRestarted = false;

	while (m_GameScreen.isOpen()) {

		m_GameScreen.clear();

		while (m_GameScreen.pollEvent(m_ScreenEvents)) {
			switch (m_ScreenEvents.type)
			{
			case sf::Event::Closed:
				m_GameScreen.close();
				break;
			}
		}

		// Restarting both dots and intro frames clock
		if (!IsLogoRestarted) {
			LogoClock.restart();
			m_LogoSound.play();
			IsLogoRestarted = true;
		}

		if (LogoClock.getElapsedTime().asSeconds() > 1.9 && LogoClock.getElapsedTime().asSeconds() < 3.9) {
			m_GameScreen.draw(m_LogoSprites[0]);
		}
		else if (LogoClock.getElapsedTime().asSeconds() > 3.9 && LogoClock.getElapsedTime().asSeconds() < 5.5) {
			m_GameScreen.draw(m_LogoSprites[1]);
		}
		else if (LogoClock.getElapsedTime().asSeconds() > 5.5) {
			m_GameScreen.draw(m_LogoSprites[2]);
		}
		
		if (m_LogoSound.getStatus() == sf::Sound::Stopped) {
			return;
		}
		
		m_GameScreen.display();
	}
}
//-----------------------------------------------//
void WindowGraphic::DisplayLoadingIntro()
{
	// Not nesuccery but part of the effect but defined here becuase in the end of the scope
	// there is no need in those objects at all
	sf::CircleShape Dot1{ 6 }, Dot2{ 6 }, Dot3{ 6 };

	Dot1.setPosition(760, 570);
	Dot2.setPosition(780, 570);
	Dot3.setPosition(800, 570);

	Dot1.setFillColor(sf::Color(165, 79, 22, 255));
	Dot2.setFillColor(sf::Color(165, 79, 22, 255));
	Dot3.setFillColor(sf::Color(165, 79, 22, 255));

	sf::Clock IntroClock;
	sf::Clock IntroDotsClock;

	bool IsIntroRestarted = false;

	while (m_GameScreen.isOpen()) {

		m_GameScreen.clear();

		while (m_GameScreen.pollEvent(m_ScreenEvents)) {
			switch (m_ScreenEvents.type)
			{
			case sf::Event::Closed:
				m_GameScreen.close();
				break;
			}
		}

		// Restarting both dots and intro frames clock
		if (!IsIntroRestarted) {
			IntroClock.restart();
			IntroDotsClock.restart();
			IsIntroRestarted = true;
		}

		// Dots drawing 
		if (IntroDotsClock.getElapsedTime().asSeconds() < 0.5) {
			m_GameScreen.draw(Dot1);
		}
		else if (IntroDotsClock.getElapsedTime().asSeconds() < 1) {
			m_GameScreen.draw(Dot1);
			m_GameScreen.draw(Dot2);
		}
		else if (IntroDotsClock.getElapsedTime().asSeconds() < 1.5) {
			m_GameScreen.draw(Dot1);
			m_GameScreen.draw(Dot2);
			m_GameScreen.draw(Dot3);
		}
		else if (IntroDotsClock.getElapsedTime().asSeconds() < 2) {
			IntroDotsClock.restart();
		}

		for (int index = 0; index < INTRO_FRAMES; ++index)
		{
			// Each second changing the frames
			if (IntroClock.getElapsedTime().asSeconds() < index + 1 && IntroClock.getElapsedTime().asSeconds() > index) {
				m_GameScreen.draw(m_IntroSprites[index]);
				break;
			}
			else if (IntroClock.getElapsedTime().asSeconds() > INTRO_FRAMES) { // Checking whether intro has finished
				return;
			}
		}

		m_GameScreen.display();
	}
}
//-----------------------------------------------//
void WindowGraphic::RunMenuPage(const sf::Vector2i& MousePos)
{
	// Define static bool array for the button Decreasement effect //
	// 0 = Play, 1 = Help, 2 = Sound, 3 = Exit //
	static bool OnIt[4] = { false, false, false, false };

	if (m_ScreenEvents.type == sf::Event::MouseMoved) {
		for (int index = 0; index < MENU_SPRITES - 1; ++index) {
			if (m_ButtonsArea[index].contains(MousePos) && OnIt[index] == false) {
				m_MenuSprites[index + 1].setScale(0.9f, 0.9f);
				OnIt[index] = true;

				break;
			}
			else if (!m_ButtonsArea[index].contains(MousePos) && OnIt[index] == true) {
				m_MenuSprites[index + 1].setScale(1.0f, 1.0f);
				OnIt[index] = false;

				break;
			}
		}
	}

	// When pressed on the Start button we change the ButtonPressed //
	// array in order to run the Play page //
	if (m_ScreenEvents.type == sf::Event::MouseButtonReleased &&
		m_ScreenEvents.mouseButton.button == sf::Mouse::Left && OnIt[0] == true) {

		m_ButtonPressed[0] = false;// running the menu page is over
		m_ButtonPressed[1] = true;// running the Play page is started
		m_MenuSprites[1].setScale(1.0f, 1.0f);
		OnIt[0] = false;
		return;
	}
	else if (m_ScreenEvents.type == sf::Event::MouseButtonReleased &&
		m_ScreenEvents.mouseButton.button == sf::Mouse::Left && OnIt[1] == true) {

		m_ButtonPressed[0] = false;// running the menu page is over
		m_ButtonPressed[2] = true;// running the Help page is started
		m_MenuSprites[2].setScale(1.0f, 1.0f);
		OnIt[1] = false;
		return;
	}
	else if (m_ScreenEvents.type == sf::Event::MouseButtonReleased && 
		m_ScreenEvents.mouseButton.button == sf::Mouse::Left && OnIt[2] == true) {

		// If sound button has been pressed and the sound is on
		// we set the button to be true in order that the DisplayMyWindow
		// function will stop the music
		if (!m_ButtonPressed[3]) {
			m_MenuSprites[3].setColor(sf::Color(255, 255, 255, 150));
			m_ButtonPressed[3] = true;
		}
		else {
			m_MenuSprites[3].setColor(sf::Color(255, 255, 255, 255));
			m_ButtonPressed[3] = false;
		}

		m_MenuSprites[3].setScale(1.0f, 1.0f);
		OnIt[2] = false;
	}
	else if (m_ScreenEvents.type == sf::Event::MouseButtonReleased &&
		m_ScreenEvents.mouseButton.button == sf::Mouse::Left && OnIt[3] == true) {

		m_GameScreen.close();
		return;
	}

	// Drawing menu sprites //
	for (int index = 0; index < MENU_SPRITES; ++index) {
		m_GameScreen.draw(m_MenuSprites[index]);
	}
}
//-------------------------------------------//
void WindowGraphic::RunStartPage(const sf::Vector2i& MousePos)
{
	m_GameScreen.setView(m_GameView);

	m_GameBackround.setPosition(m_GameView.getCenter());

	m_GameScreen.draw(m_GameBackround);
}
//-------------------------------------------//
void WindowGraphic::SetGameView(const Monkey& GivenMonkey)
{
	// Updating the view only if the monkey passed the half of the view screed by jumping up
	if (GivenMonkey.GetObjectSprite().getPosition().y < m_GameView.getCenter().y) {
		m_GameView.setCenter(m_GameView.getCenter().x, GivenMonkey.GetObjectSprite().getPosition().y);
	}

	// When the monkey disposed status is positive we reset the game view
	if (GivenMonkey.GetDisposedStatus()) {
		m_GameView.setCenter(sf::Vector2f(float(SCREEN_WIDTH) / 2, float(SCREEN_HEIGHT) / 2));
	}
}
//-------------------------------------------//
sf::View WindowGraphic::GetGameView() const
{
	return m_GameView;
}
//-------------------------------------------//
void WindowGraphic::HomePageReset()
{
	for (int i = 0; i < MENU_SPRITES - 1; i++)
	{
		if (m_ButtonPressed[i] == true) {
			m_ButtonPressed[i] = false;
			break;
		}
	}

	m_ButtonPressed[0] = true;

	m_GameView.setCenter(m_MenuSprites[0].getGlobalBounds().width / 2, m_MenuSprites[0].getGlobalBounds().height / 2);
	m_GameScreen.setView(m_GameView);
}
//-------------------------------------------//
void WindowGraphic::RunHelpPage(const sf::Vector2i& MousePos)
{
	m_GameScreen.draw(m_HelpPageSprite);
	m_GameScreen.draw(m_HomeButtonSprite);

	static bool OnIt = false; // For the Back button

	if (m_ScreenEvents.type == sf::Event::MouseMoved) {
		if (m_HomeButtonArea.contains(MousePos) && OnIt == false) {
			m_HomeButtonSprite.setScale(0.9f, 0.9f);
			OnIt = true;
		}
		else if (!m_HomeButtonArea.contains(MousePos) && OnIt == true) {
			m_HomeButtonSprite.setScale(1.0f, 1.0f);
			OnIt = false;
		}
	}

	if (m_ScreenEvents.type == sf::Event::MouseButtonReleased &&
		m_ScreenEvents.mouseButton.button == sf::Mouse::Left && OnIt == true) {

		m_ButtonPressed[2] = false;// running the help page is over
		m_ButtonPressed[0] = true;// running the menu page is started
		m_HomeButtonSprite.setScale(1.0f, 1.0f);
		OnIt = false;
	}
}
//-----------------------------------------------//
void WindowGraphic::RunSoundPage()
{

}
//-----------------------------------------------//