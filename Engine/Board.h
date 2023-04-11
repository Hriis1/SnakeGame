#pragma once
#include <random>

#include "Graphics.h"
#include "Location.h"

enum class CellContents
{
	Empty, Goal, Obsticle, Poison
};

class Board
{
	friend class Goal;
public:
	Board(Graphics& gfx);

	void drawCell(const Location& loc, Color col);
	void DrawBorder(Color color);
	void DrawContents(Color goalColor, Color obsticleColor);

	void spawnObstacle(std::mt19937& rng, const class Snake& snake, const class Goal& goal);

	bool isInsideBoard(const Location& loc) const;
	bool checkForObstacle(const Location& loc) const;

	//getters
	int getWidth() const { return _width; }
	int getHeight() const { return _height; }
	int getBoardXOffset() const { return _boardXOffset; }
	int getBoardYOffset() const { return _boardYOffset; }

private:
	void CenterBoard();
private:
	static constexpr int _dimention = 20;
	static constexpr int _width = 25;
	static constexpr int _height = 25;

	int _xOffset = 0;
	int _yOffset = 0;
	int _boardXOffset = 0;
	int _boardYOffset = 0;

	CellContents _contents[_width * _height] = { CellContents::Empty };

	Graphics& _gfx;
};

