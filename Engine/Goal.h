#pragma once
#include "Snake.h"
#include "Board.h"

#include <random>

class Goal
{
public:
	Goal(std::mt19937& rng, const Board& board, const Snake& snake);
	~Goal();

	void Respawn(std::mt19937& rng, const Board& board, const Snake& snake);
	void Draw(Board& board) const;

	//getters
	const Location& getLocation() const { return _loc; }
private:
	static constexpr Color _col = Colors::Red;
	Location _loc;
};

