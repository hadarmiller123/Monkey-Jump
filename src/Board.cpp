#include "Board.h"
//-------------------------------------------//
Board::Board() : m_BoardWidth(0), m_BoardHeight(0)
{
	if (!m_BoardFile.is_open())
		m_BoardFile.open("Board.txt", std::ios::in);// opening the file for reading only

    LoadNewBoard();
}
//-------------------------------------------//
bool Board::LoadNewBoard()
{
    // When trying to read another level we free the last one
    if (m_MyBoard != NULL) {
        FreePreviousLevel();
    }

    // Reading first the board width data
    m_BoardFile >> m_BoardWidth;

    // when file is over (Level are finished) we close the file and open it again for new game + sending game over value
    if (m_BoardFile.eof()) {
        return GAME_OVER;
    }

    // If made until here we continue to read the board height data
    m_BoardFile >> m_BoardHeight;

    // Allocation chars array
    m_MyBoard = new(std::nothrow) char* [m_BoardHeight];
    if (m_MyBoard == NULL) {
        exit(EXIT_FAILURE);
    }
    
    for (int row = 0; row < m_BoardHeight; ++row) {
        m_MyBoard[row] = new char[m_BoardWidth];
        if (m_MyBoard[row] == NULL) {
            exit(EXIT_FAILURE);
        }
    }

    for (int row = 0; row < m_BoardHeight; ++row) {
        for (int col = 0; col < m_BoardWidth; ++col) {
            m_BoardFile.get(m_MyBoard[row][col]);

            if (m_MyBoard[row][col] == '\n') { // Beacuse BoardFile.get() takes Enter as well
                --col; // So we want to override the \n by the next char
            }
        }
    }

    return !GAME_OVER;
}
//-------------------------------------------//
void Board::BuildObjectsVectors(std::vector<std::unique_ptr<MovingObject>>& Movables,
    std::vector<std::unique_ptr<StaticObject>>& Statics)
{
    // Inserting and init the vectors with the chars board from the buttom right
    // to up left
    for (int Hight = m_BoardHeight - 1; Hight >= 0; --Hight) {
        for (int Width = m_BoardWidth - 1; Width >= 0; --Width) {

            sf::Vector2f Position{ float(SCREEN_WIDTH - (100 * (m_BoardWidth - Width - 1)) - 50),
                        float(SCREEN_HEIGHT - (100 * (m_BoardHeight - Hight - 1)) - 50) };
            
            // Monkey will be modify in the end of the vector for easy access method
            if (Factory<MovingObject>::instance().IsExist(m_MyBoard[Hight][Width])) {
                if (m_MyBoard[Hight][Width] == 'M') {
                    Movables.push_back(Factory<MovingObject>::instance().create((ObjectType)m_MyBoard[Hight][Width], Position));
                }
                else {
                    Movables.insert(Movables.begin(), Factory<MovingObject>::instance().create((ObjectType)m_MyBoard[Hight][Width], Position));
                }
            }
            else if (Factory<StaticObject>::instance().IsExist(m_MyBoard[Hight][Width])) {
                Statics.push_back(Factory<StaticObject>::instance().create((ObjectType)m_MyBoard[Hight][Width], Position));
            }
        }
    }
}
//-------------------------------------------//
void Board::FreePreviousLevel()
{
    for (int row = 0; row < m_BoardHeight; ++row) {
        delete[] m_MyBoard[row];
    }
    delete[] m_MyBoard;
    m_MyBoard = NULL;
}
//-------------------------------------------//
Board::~Board()
{
    if (m_MyBoard != NULL) {
        for (int row = 0; row < m_BoardHeight; ++row) {
            delete[] m_MyBoard[row];
        }
        delete[] m_MyBoard;
        m_MyBoard = NULL;
    }

    m_BoardFile.close();
}
//-------------------------------------------//