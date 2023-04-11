#include "Goal.h"

Goal::Goal(std::mt19937& rng, Board& board, const Snake& snake)
{
	Respawn(rng, board, snake);
}

Goal::~Goal()
{
}

void Goal::Respawn(std::mt19937& rng, Board& board, const Snake& snake)
{
	std::uniform_int_distribution<int> xDist(0, board.getWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, board.getHeight() - 1);

	board._contents[_loc._y * board._width + _loc._x] = CellContents::Empty;
	Location newLoc;
	do
	{
		newLoc._x = xDist(rng);
		newLoc._y = yDist(rng);
	} while (snake.IsInTile(newLoc) || board.checkForObstacle(newLoc));

	_loc = newLoc;
	board._contents[_loc._y * board._width + _loc._x] = CellContents::Goal;

}
