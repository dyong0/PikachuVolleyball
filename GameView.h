#pragma once

class Game;

class GameView
{
public:
	std::string name;

	GameView(Game* game);
	~GameView();

	virtual void processKey(int key) = 0;

protected:
	Game* game;
};
