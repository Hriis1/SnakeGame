#pragma once

struct Location
{
public:
	Location()
		: _x(0), _y(0) {}

	Location(int x, int y)
		: _x(x), _y(y) {}

	~Location() {}

	void Add(const Location& other)
	{
		_x += other._x;
		_y += other._y;
	}

	//operators
	bool operator==(const Location& other) const
	{
		return _x == other._x && _y == other._y;
	}

	bool operator!=(const Location& other) const
	{
		return !operator==(other);
	}

public:
	int _x;
	int _y;

};
