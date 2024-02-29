#include "Controller.h"
//-----------------------------------------------//
Controller::Controller() : m_GameBoard(std::make_unique<Board>())
{
	BuildObjectsVectors();
}
//-----------------------------------------------//
void Controller::Run()
{
	m_WindowG.DisplayGameIntro();

	while (m_WindowG.GetMyWindow().isOpen()) {
		if (m_WindowG.DisplayMyWindow()) {

			// First moving the objects
			MoveObjects();

			// Second drawing them to show the player a clear vision of what is the updated frame
			// should be and displaying it right after drawing (Before collision is happening)
			DrawGameObjects();

			// Third we display the game objects that has been drawn
			m_WindowG.GetMyWindow().display();

			// and only then checking for collisions, updating the floors status, clearing the unessucery objects,
			// updating the game view according to the monkey position
			// and only then checking if a new level needs to be loaded or a reset has needs to be made
			HandleCollisions();

			UpdateFloorsVisibility();

			ClearUndisposedObjects();

			// Second Sending the monkey we already know his cell and updating the view according to monkey position sprite
			m_WindowG.SetGameView(static_cast<Monkey&>(*m_Movables[m_MonkeyCell]));

			ResetOrNextLevel();
			
			// Continuing becuase window already displayed in game loop
			continue;
		}

		m_WindowG.GetMyWindow().display();
	}
}
//-----------------------------------------------//
void Controller::BuildObjectsVectors()
{
	try
	{
		m_GameBoard->BuildObjectsVectors(m_Movables, m_Statics);

		// Throwing exception when text file not contain objects or for some reason board class
		// didn't add noting to the vectors
		if (m_Movables.size() == 0 || m_Statics.size() == 0) {
			throw std::runtime_error{"Vectors cannot be empty"};
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	// Monkey will be at the last in the movables vector, that way we will gain premitive access to it
	m_MonkeyCell = m_Movables.size() - 1;
}
//-----------------------------------------------//
void Controller::MoveObjects()
{
	// Calling move for each movable
	for (auto it = m_Movables.begin(); it != m_Movables.end(); ++it) {
		it->get()->Move();
	}
}
//-----------------------------------------------//
void Controller::DrawGameObjects()
{
	// Drawing static objects
	for (int i = 0; i < m_Statics.size(); i++) {
		m_Statics[i]->Draw(m_WindowG.GetMyWindow());
	}

	// Drawing moving objects
	for (int i = 0; i < m_Movables.size(); ++i) {
		m_Movables[i]->Draw(m_WindowG.GetMyWindow());
	}
}
//-----------------------------------------------//
void Controller::HandleCollisions()
{
	// Checking collisions moving - statics
	for (int i = 0; i < m_Movables.size(); ++i) {
		for (int j = 0; j < m_Statics.size(); ++j) {
			if (m_Movables[i]->IsCollide(*m_Statics[j])) {
				ProccessCollision(*dynamic_cast<BaseGameObject*>(m_Movables[i].get()), *dynamic_cast<BaseGameObject*>(m_Statics[j].get()));
			}
		}
	}

	// Checking collisions moving - moving
	for (int i = 0; i < m_Movables.size(); ++i) 
	{
		for (int j = 0; j < m_Movables.size(); ++j) {
			if (m_Movables[i]->IsCollide(*m_Movables[j])) {
				ProccessCollision(*dynamic_cast<BaseGameObject*>(m_Movables[i].get()), *dynamic_cast<BaseGameObject*>(m_Movables[j].get()));
			}
		}
	}
}
//-----------------------------------------------//
void Controller::UpdateFloorsVisibility()
{
	// Making dynamic casting in order to find floor objects in order to update their visibility
	// vs the monkey whether he can jump on them or jump throgh them from down
	// cant use static cast or any other methods becuase that in multiple virtual inheritance
	// there is no option to make static cast, the compiler doesnt know how to gain access in the memoryin compile time
	// (offset that need to be calculated in order to move the the right object cant be done in compile time)
	for (int i = 0; i < m_Statics.size(); ++i) {
		Floor* FloorHolder = dynamic_cast<Floor*>(m_Statics[i].get());
		if (FloorHolder) {
			FloorHolder->UpdateMyVisibilityStatus(static_cast<Monkey&>(*m_Movables[m_MonkeyCell]));
		}
	}

	// Same for moving floors
	for (int i = 0; i < m_Movables.size(); ++i) {
		Floor* FloorHolder = dynamic_cast<Floor*>(m_Movables[i].get());
		if (FloorHolder) {
			FloorHolder->UpdateMyVisibilityStatus(static_cast<Monkey&>(*m_Movables[m_MonkeyCell]));
		}
	}
}
//-----------------------------------------------//
void Controller::ClearUndisposedObjects()
{
	// Movables clearing
	for (int i = 0; i < m_Movables.size(); ++i) {
		if (m_Movables[i]->GetObjectSprite().getGlobalBounds().top >
			m_WindowG.GetGameView().getCenter().y + m_WindowG.GetGameView().getSize().y / 2) {
			m_Movables[i]->SetDisposedStatus();
		}

		// erasing every object that needs to be erase except the monkey 
		// (reason its becuase that we will still need him to know whether he passed
		// the finish line or for checking whether he has been killed (and we check it in the ResetOrNextLevel function)
		if (m_Movables[i]->GetDisposedStatus() && typeid(*m_Movables[i]) != typeid(Monkey)) {
			m_Movables.erase(m_Movables.begin() + i);
			
			// Updating Monkey cell number in the vector after erasing object
			m_MonkeyCell = m_Movables.size() - 1;
		}
	}

	// Statics clearing
	for (int i = 0; i < m_Statics.size(); ++i) {
		if (m_Statics[i]->GetObjectSprite().getGlobalBounds().top >
			m_WindowG.GetGameView().getCenter().y + m_WindowG.GetGameView().getSize().y / 2) {
			m_Statics[i]->SetDisposedStatus();
		}

		if (m_Statics[i]->GetDisposedStatus()) {
			m_Statics.erase(m_Statics.begin() + i);
		}
	}
}
//-----------------------------------------------//
void Controller::ResetOrNextLevel()
{
	Monkey& MonkeyHolder = static_cast<Monkey&>(*m_Movables[m_MonkeyCell]);

	// If the monkey has been collide and finish we need to try and load the next level
	// and clear the vectors in order to send then to board that will load new level
	if (MonkeyHolder.GetFinishedStatus()) {
		ClearGameVectors();

		if (!m_GameBoard->LoadNewBoard()) {
			BuildObjectsVectors();
			return;
		}
		// else if there is no more levels = you won the game
		else {
			ResetGameBoard();
			return;
		}
	}
	else if (MonkeyHolder.GetDisposedStatus()) {
		ClearGameVectors();
		BuildObjectsVectors();
	}
}
//-----------------------------------------------//
void Controller::ResetGameBoard()
{
	// calling the reset function of window controller plus replacing the old board by a new one and building vectors again
	m_WindowG.HomePageReset();
	m_GameBoard = std::make_unique<Board>();
	BuildObjectsVectors();
}
//-----------------------------------------------//
void Controller::ClearGameVectors()
{
	m_Movables.clear();
	m_Statics.clear();
}
//-----------------------------------------------//