#include <iostream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "Level.h"
using namespace std;

class BasicTile : public ITile
{
private:
	const char _character;
	const bool _canEnter;

public:
	BasicTile(char ch, bool canEnter) : _character(ch), _canEnter(canEnter)
	{

	}

	virtual char GetCharacter() const { return _character; }
	virtual bool CanEnter(IEntity& entity) { return _canEnter; }
	virtual void Enter(IEntity& entity) {};
};

class BasicEntity : public IEntity
{
	char _character;
	Position _position;

public:
	BasicEntity(char ch) : _character(ch), _position(0, 0)
	{
	}

	virtual char GetCharacter() const { return _character; }
	virtual const Position& GetPosition() const { return _position; }
	virtual void SetPosition(const Position& position) { _position = position; }
	virtual void Collide(IEntity& entity) { }
	virtual void Update() { }
};

int main()
{
	Level level(20, 20);
	BasicTile empty(' ', true);
	BasicTile wall('#', false);

	level.SetTiles(empty, Position(0, 0), Position(19, 19));
	level.SetTiles(wall, Position(0, 0), Position(0, 19));
	level.SetTiles(wall, Position(0, 0), Position(19, 0));
	level.SetTiles(wall, Position(19, 0), Position(19, 19));
	level.SetTiles(wall, Position(0, 19), Position(19, 19));

	level.SetTiles(wall, Position(4, 4), Position(6, 6));
	//level.SetTiles(wall, Position(10, 20), Position(10, 22));
	//level.SetTiles(wall, Position(10, 20), Position(10, 22));

	BasicEntity player('$');
	level.SetEntity(player, Position(1, 1));

	char input = '\0';

	level.RenderAll();
	auto lastTime = timeGetTime();

	while (input != 27)//27 is the ASCII code for the escape key
	{

		auto currentElapsed = timeGetTime() - lastTime;
		if (currentElapsed > 33.3)
		{
			lastTime = timeGetTime();//this was added into project from the Winmm.lib
			level.Update();
		}

		if (_kbhit())//if the keyboard is hit
		{
			input = _getch();
			auto pos = player.GetPosition();
			if (input == 'w')//up
				level.MoveEntity(player, Position(pos.GetX(), pos.GetY() - 1));
			else if (input == 'a')//left
				level.MoveEntity(player, Position(pos.GetX() - 1, pos.GetY()));
			else if (input == 's')//down
				level.MoveEntity(player, Position(pos.GetX(), pos.GetY() + 1));
			else if (input == 'd')//right
				level.MoveEntity(player, Position(pos.GetX() + 1, pos.GetY()));
		}
	}

	std::cin.get();
	return 0;
}