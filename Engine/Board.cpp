#include "Board.h"
#include "Snake.h"
#include "Goal.h"

#include <assert.h>

Board::Board(Graphics& gfx)
	: _gfx(gfx)
{
	CenterBoard();
}

void Board::drawCell(const Location& loc, Color col)
{
	assert(loc._x >= -_boardXOffset);
	assert(loc._x < _width + _boardXOffset);
	assert(loc._y >= -_boardYOffset);
	assert(loc._y < _height + _boardYOffset);

	_gfx.DrawRectDim(loc._x * _dimention + _xOffset, loc._y * _dimention + _yOffset, _dimention, _dimention, col);
}

void Board::DrawBorder(Color color)
{
	//Draw horizonta borders
	for (size_t x = 0; x < _width; x++)
	{
		drawCell(Location(x, -1), color);
		drawCell(Location(x, _height), color);
	}

	//Draw vertical borders
	for (size_t y = 0; y < _height; y++)
	{
		drawCell(Location(-1, y), color);
		drawCell(Location(_width, y), color);
	}
}

void Board::DrawContents(Color goalColor, Color obsticleColor)
{
	for (size_t i = 0; i < _width * _height; i++)
	{
		int x = i % _width;
		int y = i / _width;
		if (_contents[i] == CellContents::Obsticle)
		{
			Location obstacleLoc(x,y);
			drawCell(obstacleLoc, obsticleColor);
		}
		else if (_contents[i] == CellContents::Goal)
		{
			drawCell(Location(x, y), goalColor);
		}

	}
}

void Board::spawnObstacle(std::mt19937& rng, const Snake& snake, const Goal& goal)
{
	std::uniform_int_distribution<int> xDist(0, _width - 1);
	std::uniform_int_distribution<int> yDist(0, _height - 1);

	Location newLoc;
	do
	{
		newLoc._x = xDist(rng);
		newLoc._y = yDist(rng);
	} while (snake.IsInTile(newLoc) || checkForObstacle(newLoc) || newLoc == goal.getLocation());

	_contents[newLoc._y * _width + newLoc._x] = CellContents::Obsticle;
}

bool Board::isInsideBoard(const Location& loc) const
{
	
	bool inBoard =  loc._x >= 0 && loc._x < _width && loc._y >= 0 && loc._y < _height;
	return inBoard;
}

bool Board::checkForObstacle(const Location& loc) const
{
	return _contents[loc._y * _width + loc._x] == CellContents::Obsticle;
}

void Board::CenterBoard()
{
	int xSize = _dimention * _width;
	int ySize = _dimention * _height;

	_xOffset = (Graphics::ScreenWidth - xSize) / 2;
	_yOffset = (Graphics::ScreenHeight - ySize) / 2;

	_boardXOffset = _xOffset / _dimention;
	_boardYOffset = _yOffset / _dimention;
}
