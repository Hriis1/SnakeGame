#pragma once

#include <vector>
#include <random>

#include "Board.h"
#include "Location.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& loc);
		void InitBody(std::mt19937& bodyColRng, std::uniform_int_distribution<int>& bodyColDist);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& board) const;

		//getters
		const Location& GetLocation() const { return _loc; }

	private:
		Location _loc;
		Color _col;
	};

public:
	Snake(const Location& loc);
	~Snake();

	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& board) const;

	Location GetNextHeadPos(const Location& delta_loc) const;
	bool IsInTile(const Location& target) const;
	bool IsInTileExeptEnd(const Location& target) const;

private:
	static constexpr Color _headColor = Colors::Yellow;
	static constexpr Color _bodyBaseColor = Colors::Green;

	std::mt19937 _bodyColRng;
	std::uniform_int_distribution<int> bodyColDist;

	int _startSize = 1;
	std::vector<Segment> _segments;


};

