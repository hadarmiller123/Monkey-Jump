#pragma once
//-------------------------------------------//
#include <fstream>
#include "Resources.h"
#include "MovingObject.h"
#include "StaticObject.h"
#include <Factory.h>
//-------------------------------------------//
using std::ifstream;
//-------------------------------------------//
const bool GAME_OVER = true;
//-------------------------------------------//
class Board
{
public:
	Board();
	~Board();

	// Returns true if new level has been loaded and false if end of the file accured
	bool LoadNewBoard();

	void BuildObjectsVectors(std::vector<std::unique_ptr<MovingObject>>& Movables,
		std::vector<std::unique_ptr<StaticObject>>& Statics);
private:
	void FreePreviousLevel();
private:
	// General board variables //
	ifstream m_BoardFile;
	char** m_MyBoard = NULL;
	int m_BoardWidth;
	int m_BoardHeight;
};
//-------------------------------------------//