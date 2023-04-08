#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx);

	void drawCell(const Location& loc, Color col);
	void DrawBorder(Color color);

	bool isInsideBoard(const Location& loc) const;

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

	Graphics& _gfx;
};

