#include "Snake.h"
#include <assert.h>

void Snake::Segment::InitHead(const Location& loc)
{
	_loc = loc;
	_col = Snake::_headColor;
}

void Snake::Segment::InitBody(std::mt19937& bodyColRng, std::uniform_int_distribution<int>& bodyColDist)
{
	_col = Color(_bodyBaseColor.GetR(), bodyColDist(bodyColRng), _bodyBaseColor.GetB());
}

void Snake::Segment::Follow(const Segment& next)
{
	_loc = next._loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc._x) + abs(delta_loc._y) == 1);

	_loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& board) const
{
	board.drawCell(_loc, _col);
}

Snake::Snake(const Location& loc)
	: _bodyColRng(std::random_device()()), bodyColDist(100,255)
{
	_segments.resize(1);
	_segments[0].InitHead(loc);
}

Snake::~Snake()
{
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (size_t i = _segments.size() - 1; i > 0; i--)
	{
		_segments[i].Follow(_segments[i - 1]);
	}
	_segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	_segments.emplace_back();
	_segments.back().InitBody(_bodyColRng,bodyColDist);
}

void Snake::Draw(Board& board) const
{
	for (size_t i = 0; i < _segments.size(); i++)
	{
		_segments[i].Draw(board);
	}
}

Location Snake::GetNextHeadPos(const Location& delta_loc) const
{
	Location l(_segments[0].GetLocation());
	l.Add(delta_loc);
	return l;
}

bool Snake::IsInTile(const Location& target) const
{
	for (size_t i = 0; i < _segments.size(); i++)
	{
		if (_segments[i].GetLocation() == target)
		{
			return true;
		}
	}

	return false;
}

bool Snake::IsInTileExeptEnd(const Location& target) const
{
	for (size_t i = 0; i < _segments.size() - 1; i++)
	{
		if (_segments[i].GetLocation() == target)
		{
			return true;
		}
	}

	return false;
}

