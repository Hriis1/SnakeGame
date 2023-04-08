#include "Goal.h"

Goal::Goal(std::mt19937& rng, const Board& board, const Snake& snake)
{
	Respawn(rng, board, snake);
}

Goal::~Goal()
{
}

void Goal::Respawn(std::mt19937& rng, const Board& board, const Snake& snake)
{
	std::uniform_int_distribution<int> xDist(0, board.getWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, board.getHeight() - 1);

	Location newLoc;
	do
	{
		newLoc._x = xDist(rng);
		newLoc._y = yDist(rng);
	} while (snake.IsInTile(newLoc));

	_loc = newLoc;

}

void Goal::Draw(Board& board) const
{
	board.drawCell(_loc, _col);
}
