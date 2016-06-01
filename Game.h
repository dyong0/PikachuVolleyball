#pragma once

#include <string>
#include <queue>

#include <boost/unordered_map.hpp>

#include "GameView.h"
#include "Player.h"
#include "UserPlayer.h"
#include "AIPlayer.h"

enum GameMode{
	GAME_MODE_PLAY_ALONE = 1,
	GAME_MODE_PLAY_WITH_FRIEND = 2
};

class Game
{
public:
	static const float DEFAULT_FPS;

	static Game* getInstance();

	std::queue<int>* getInputQueue();

	void init();
	void run();

	Player* getPlayer(int index);

private:
	static std::queue<int>* keyInputQueue;
	static Game* instance;

	bool running;
	float fps;
	GameView* currentView;
	boost::unordered_map<std::string, GameView*> views;

	GameMode gameMode;

	Player* players[2] = {};

	Game();
	~Game();
	void initViews();
	void registerGameView(std::string viewName, GameView* view);
	int getLastInputKey();
	void getInput();
	void reset();
	void quit();
	void startGameAlone();
	void startGameWithFriend();
	void startGame();
	void changeView(std::string viewName);

	void onFatalException(std::exception const& e);
};