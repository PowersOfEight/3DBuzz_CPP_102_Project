#pragma once
#ifndef POSITION_H
#define	POSITION_H

class Position
{
	int _x, _y;

public:
	Position(int x, int y);

	int GetX() const;
	int GetY() const;
};
//commit this

#endif // ! POSITION_H