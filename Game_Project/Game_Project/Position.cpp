#include "Position.h"

Position::Position(int x, int y) : _x(x), _y(y)
{

}

int Position::GetX() const { return _x; }
int Position::GetY() const { return _y; }