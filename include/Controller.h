#pragma once
//-----------------------------------------------//
#include <vector>
#include <memory>
#include "WindowGraphic.h"
#include "Resources.h"
#include "Board.h"
#include "BaseGameObject.h"
#include "MovingObject.h"
#include "StaticObject.h"
#include "CollisionHandling.h"
//-----------------------------------------------//
class Controller
{
public:
	Controller();
	void Run();
private:
	void BuildObjectsVectors();
	void MoveObjects();
	void DrawGameObjects();
	void HandleCollisions();
	void UpdateFloorsVisibility();
	void ClearUndisposedObjects();
	void ResetOrNextLevel();
	void ResetGameBoard();
	void ClearGameVectors();
private:
	WindowGraphic m_WindowG; // for window graphic

	std::unique_ptr<Board> m_GameBoard;

	// Will be useful to be able to gain access to the monkey object
	size_t m_MonkeyCell = 0;
	std::vector<std::unique_ptr<MovingObject>> m_Movables;
	std::vector<std::unique_ptr<StaticObject>> m_Statics;
};
//-----------------------------------------------//